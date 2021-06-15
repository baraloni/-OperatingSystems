
#include "uthreads.h"
#include "thread_manager.h"
#include "scheduler.h"
#include "virtual_timer.h"
#include "real_timer.h"
#include "sleeping_threads_list.h"

#include <signal.h>


//--------------Consts:
static const int CONVERT_CONST_SEC_TO_NSEC = 1000000000;
static const int CONVERT_CONST_MSEC_TO_NSEC = 1000;

//-------------Error Massages:
static const int sysError = -2;

static std::string libErrorSyntax =  "thread library error: ";
static std::string sysErrorSyntax = "system error: ";

//-------------Static Globals:
static struct sigaction saVTimer;
static struct sigaction saRTimer;
static SleepingThreadsList* sleepingThreads;
static thread_manager* manager;
static scheduler* scheduler;
static virtual_timer* vTimer;
static real_timer* rTimer;
static int totalQuants = 0;
static sigset_t toBlock;        // A set of signals to block where critical code is executed.

//-------------Sleep
/**
 * Computes the time of day in which the thread is going to wake up.
 * @param usecs_to_sleep
 * @return
 */
static timeval calcWakUpTimeval(int usecs_to_sleep) {

    timeval now, time_to_sleep, wake_up_timeval;
    gettimeofday(&now, nullptr);
    time_to_sleep.tv_sec = usecs_to_sleep / 1000000;
    time_to_sleep.tv_usec = usecs_to_sleep % 1000000;
    timeradd(&now, &time_to_sleep, &wake_up_timeval);
    return wake_up_timeval;
}

//------------Memory Management
/**
 * Clears the library resources.
 */
static void clearMem(){
    delete scheduler;
    delete manager;
    delete vTimer;
    delete sleepingThreads;
    delete rTimer;
}

/**
 * Clears the system memory and exits.
 * @param errMsg: The error message to be printed in the case of a system call.
 */
static void exitProg(const std::string& errMsg){
    clearMem();
    std::cerr << sysErrorSyntax << errMsg << std::endl;
    exit(1);
}

//-------------Masking:
static void maskSignals(){
    if(sigprocmask(SIG_BLOCK, &toBlock, nullptr) < 0){
        exitProg("Failed to set signal masking.");
    }
}

static void unmaskSignals(){
    if(sigprocmask(SIG_UNBLOCK, &toBlock, nullptr) < 0){
        exitProg("Failed to undo signal masking.");
    }
}

//-------------Signal Handlers:

/**
 * Responds when the time for the running thread has passed, and preforms a context-switch.
 * @param sig
 */
static void handleQuantumTimeout(int sig){
    // Start the _timer again & update totalQuants:
//    std::cerr <<"\n**ALARM- timeout**\n";
    if(sig == SIGVTALRM){
        if(vTimer->start() < 0){
            exitProg("Failed to start _timer.");
        }

        totalQuants++;
//    std::cerr <<"\nTIME: " << totalQuants <<std::endl;

        // Do a context switch:
        int currRun = scheduler->getRunning();
        int nextToRun = scheduler->whosNextTimeout();
        manager->switchContext(currRun, nextToRun);
    }
}

/**
 * Wakes up the signal who's timer expired.
 * @param sig
 */
static void handleSleepTimeout(int sig){
    if(sig == SIGALRM){
        int totalTime = 0;
        int inLoop = 0;
        do{
            ++inLoop;
            wake_up_info* threadToAwake = sleepingThreads->peek();
            int toWakeTid = threadToAwake->id;

            // Awake the relevant thread:
            sleepingThreads->pop();
            if(manager->wakeThread(toWakeTid) == 0){       // if thread exists (active, haven't been terminated while sleeping)
                if(!(manager->isThreadBlocked(toWakeTid))) // if thread is not blocked
                {
                    scheduler->addThread(toWakeTid);
                }
            }

            // calculate the time until the next waking:
            wake_up_info* nextToWake = sleepingThreads->peek();

            if(nextToWake != nullptr) //if there are more sleeping threads, set a new timer for the head
            {
                timeval now;
                gettimeofday(&now, nullptr);
                timeval nextWakingTime = nextToWake->awaken_tv;
                totalTime = (nextWakingTime.tv_sec - now.tv_sec) * CONVERT_CONST_SEC_TO_NSEC +
                            (nextWakingTime.tv_usec - now.tv_usec) * CONVERT_CONST_MSEC_TO_NSEC;
            } else
            {
                return;
            }
        } while(totalTime <= 0);

        // Reset the timer:
        rTimer->start(totalTime);
    }
}

//---------------------------------Library Functionality---------------------
/*
 * Description: This function initializes the thread library.
 * You may assume that this function is called before any other thread library
 * function, and that it is called exactly once. The input to the function is
 * the length of a quantum in micro-seconds. It is an error to call this
 * function with non-positive quantum_usecs.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_init(int quantum_usecs)
{
    if (quantum_usecs > 0)
    {
        // Create global functionality holders:
        manager = new thread_manager(quantum_usecs, MAX_THREAD_NUM, STACK_SIZE);
        if (manager->threadManagerSetup() == sysError) // a sys error occurred in manager setup
        {
            clearMem();
            exit(1);
        }
        vTimer = new virtual_timer(quantum_usecs);
        rTimer = new real_timer;
        scheduler = new class scheduler;
        sleepingThreads = new SleepingThreadsList;
        saVTimer = {};
        saRTimer = {};

        // Initialize the signal set to block:
        if((sigaddset(&toBlock, SIGVTALRM) < 0)||(sigaddset(&toBlock, SIGALRM) < 0)) {
            exitProg("Failed to initialize signal set to block.");
        }

        // Set signal handlers:
        saVTimer.sa_handler = &handleQuantumTimeout;
        saVTimer.sa_mask = toBlock;
        saVTimer.sa_flags = 0; // Verifies that no flags are applied.
        if(sigaction(SIGVTALRM, &saVTimer, nullptr) < 0){
            exitProg("sigaction had failed.");
        }

        saRTimer.sa_handler = &handleSleepTimeout;
        saRTimer.sa_mask = toBlock;
        saRTimer.sa_flags = 0; // Verifies that no flags are applied.
        if(sigaction(SIGALRM, &saRTimer, nullptr) < 0){
            exitProg("sigaction had failed.");
        }

        // Start _timer & update the quantum counting:
        if(vTimer->start() < 0){
            exitProg("Failed to start _timer.");
        }
        totalQuants++;

        return 0;
    }
    std::cerr << libErrorSyntax << "quantum_usec should be non-negative." << std::endl;
    return -1;
}

/*
 * Description: This function creates a new thread, whose entry point is the
 * function f with the signature void f(void). The thread is added to the end
 * of the READY threads list. The uthread_spawn function should fail if it
 * would cause the number of concurrent threads to exceed the limit
 * (MAX_THREAD_NUM). Each thread should be allocated with a stack of size
 * STACK_SIZE bytes.
 * Return value: On success, return the ID of the created thread.
 * On failure, return -1.
*/
int uthread_spawn(void (*f)()){
    maskSignals();
    int newTid = manager->createThread(f);
    if (newTid == sysError) // a sys error occurred in thread setup in manager
    {
        clearMem();
        exit(1);
    }
    else if(newTid == -1){
        std::cerr <<  libErrorSyntax << "Number of threads > MAX_THREAD_NUMBER." << std::endl;
        unmaskSignals();
        return  -1;
    }
    scheduler->addThread(newTid);
    unmaskSignals();
    return newTid;
}


/*
 * Description: This function terminates the thread with ID tid and deletes
 * it from all relevant control structures. All the resources allocated by
 * the library for this thread should be released. If no thread with ID tid
 * exists it is considered an error. Terminating the main thread
 * (tid == 0) will result in the termination of the entire process using
 * exit(0) [after releasing the assigned library memory].
 * Return value: The function returns 0 if the thread was successfully
 * terminated and -1 otherwise. If a thread terminates itself or the main
 * thread is terminated, the function does not return.
*/
int uthread_terminate(int tid)
{
    maskSignals();
    int currRunning = scheduler->getRunning();
    int nextToRun;

    if(tid != 0)
    {
        if (manager->killThread(tid) != -1)                        //If thread exists.
        {
            nextToRun = scheduler->whosNextTermination(tid);
            if(nextToRun != currRunning){                          // If we should do a context switch.
                if(vTimer->start() < 0){
                    exitProg("Failed to start _timer.");
                }
                totalQuants++;
                manager->switchContext(currRunning, nextToRun);
            }
            unmaskSignals();
            return 0;
        }
        std::cerr <<  libErrorSyntax << "Thread doesn't exit." << std::endl;
        unmaskSignals();
        return -1;
    }
    clearMem();
    unmaskSignals();
    exit(0);
}


/*
 * Description: This function blocks the thread with ID tid. The thread may
 * be resumed later using uthread_resume. If no thread with ID tid exists it
 * is considered as an error. In addition, it is an error to try blocking the
 * main thread (tid == 0). If a thread blocks itself, a scheduling decision
 * should be made. Blocking a thread in BLOCKED state has no
 * effect and is not considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_block(int tid)
{
    maskSignals();
    int currRunning = scheduler->getRunning();
    int nextToRun;

    if (tid != 0)
    {
        if(manager->blockThread(tid) != -1){                 // If thread exists.
            nextToRun = scheduler->whosNextBlock(tid);
            if(nextToRun != currRunning){                   // If we should do a context switch.
                if(vTimer->start() < 0){
                    exitProg("Failed to start _timer.");
                }
                totalQuants++;
                manager->switchContext(currRunning, nextToRun);
            }
            unmaskSignals();
            return 0;
        }
        std::cerr <<  libErrorSyntax << "Thread doesn't exit." << std::endl;
        unmaskSignals();
        return -1;
    }
    std::cerr <<  libErrorSyntax << "Blocking the main thread is forbidden." << std::endl;
    unmaskSignals();
    return -1;
}


/*
 * Description: This function resumes a blocked thread with ID tid and moves
 * it to the READY state if it's not synced. Resuming a thread in a RUNNING or READY state
 * has no effect and is not considered as an error. If no thread with
 * ID tid exists it is considered an error.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_resume(int tid)
{
    maskSignals();
    if (manager->unBlockThread(tid) != -1)
    {
       if(!manager->isThreadAsleep(tid)){
           scheduler->addThread(tid);
       }
       unmaskSignals();
       return 0;
    }
    std::cerr <<  libErrorSyntax << "Thread doesn't exit." << std::endl;
    unmaskSignals();
    return -1;
}


/*
 * Description: This function blocks the RUNNING thread for user specified micro-seconds (virtual time).
 * It is considered an error if the main thread (tid==0) calls this function.
 * Immediately after the RUNNING thread transitions to the BLOCKED state a scheduling decision
 * should be made.
 * Return value: On success, return 0. On failure, return -1.
*/
int uthread_sleep(unsigned int usec)
{
    maskSignals();
    int runningThreadTid = scheduler->getRunning();
    wake_up_info* oldFirstToWake = sleepingThreads->peek(); // NULL if the list is empty.

    if(runningThreadTid != 0){ // You can't put to sleep the main process.

        // Updating the sleeping threads list:
        timeval t = calcWakUpTimeval(usec);
        sleepingThreads->add(runningThreadTid, t);

        // Reset timer:
        wake_up_info* newFirstToWake = sleepingThreads->peek();
        if(oldFirstToWake == nullptr) {
            // If the list was empty before, the added thread is surly the head, and we should reset the timer:
            rTimer->start(usec);
        } else {
            // If the head of the list was changed, we should update the timer according to the new head:
            if(oldFirstToWake->id != newFirstToWake->id){
                rTimer->start(usec);
            }
        }

        // Now we update the manager and scheduler that the thread is sleeping:
        manager->putThreadToSleep(runningThreadTid);
        int nextToRun = scheduler->whosNextSleep();

        // And do a context-switch:
        if(vTimer->start() < 0){
            exitProg("Failed to start _timer.");
        }
        totalQuants++;
        manager->switchContext(runningThreadTid, nextToRun);
        unmaskSignals();
        return 0;
    }
    std::cerr <<  libErrorSyntax << "The main thread can't sleep." << std::endl;
    unmaskSignals();
    return -1;
}

/*
 * Description: This function returns the thread ID of the calling thread.
 * Return value: The ID of the calling thread.
*/
int uthread_get_tid()
{
    maskSignals();
    int retVal = scheduler->getRunning();
    unmaskSignals();

    return retVal;
}


/*
 * Description: This function returns the total number of quantums since
 * the library was initialized, including the current quantum.
 * Right after the call to uthread_init, the value should be 1.
 * Each time a new quantum starts, regardless of the reason, this number
 * should be increased by 1.
 * Return value: The total number of quantums.
*/
int uthread_get_total_quantums()
{
    return totalQuants;
}


/*
 * Description: This function returns the number of quantums the thread with
 * ID tid was in RUNNING state. On the first time a thread runs, the function
 * should return 1. Every additional quantum that the thread starts should
 * increase this value by 1 (so if the thread with ID tid is in RUNNING state
 * when this function is called, include also the current quantum). If no
 * thread with ID tid exists it is considered an error.
 * Return value: On success, return the number of quantums of the thread with ID tid.
 * 			     On failure, return -1.
*/
int uthread_get_quantums(int tid)
{
    maskSignals();
    int threadQuants = manager->getThreadQuants(tid);
    if (threadQuants != -1)  // If thread exists.
    {
        unmaskSignals();
        return threadQuants;
    }
    std::cerr <<  libErrorSyntax << "Thread doesn't exit." << std::endl;
    unmaskSignals();
    return -1;
}