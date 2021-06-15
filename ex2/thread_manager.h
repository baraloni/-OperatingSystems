

#ifndef OSEX2_HANDLER_H
#define OSEX2_HANDLER_H

#include <cassert>

//data structures:
#include <queue>
#include <unordered_map>
#include <cassert>

//context switch handling:
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

//classes:
#include "thread.h"


class thread_manager
{
    int _maxThreadNum;
    int _stackSize;
    int _quantumUsecs;
    int _largestId;
    std::priority_queue<int, std::vector<int>, std::greater<int>> _usedIds;
    std::unordered_map<int, thread*> _threads;


    /**
    * checks if the supplied tid represents an existing thread.
    * @param tid the tid to search by.
    * @return the address of the thread whose tid is the supplied one.
    * if no such thread exists, returns nullptr.
    */
    thread *findThread(int tid);

    /**
     * handles the tid assignments.
     * @return the smallest tid available for assignment.
     */
    int getSmallestTid();


public:

    /** constructs a thread_manager object*/
    thread_manager(int quantum_usecs, int maxThreadNum,
                   int stackSize);

    /** destructs this thread_manager object*/
    ~thread_manager();

    /**
     * initializes the thread_manager object: creates representation of main thread.
     * @return 0 on success, prints error and returns -2 on system fail.
     */
    int threadManagerSetup();

    /**
     * Creates a new thread object.
     * @param f : The function the thread should execute.
     * @return the new thread's tid, a non negative int.
      * -1 if the new thread could not be created.
      * prints an error and returns -2 if a system error occurred.
     */
    int createThread(void (*f)());

    /**
    * deletes the thread with the supplied tid, if exists.
    * @param tid: the tid of the thread we want to delete.
    * @return -1 if a thread of the supplied tid does not exist,
    *         0 if exists and erased successfully.
    */
    int killThread(int tid);

    /**
    * @param tid: the tid of the thread we want to block.
    * @return 0 if the thread exists and we succeed on blocking it,
    * -1 if it does not exist.
    */
    int blockThread(int tid);

    /**
     * @param tid: the tid of the thread we want to unblock.
     * @return 0 if the thread exists and we succeed on unblocking it,
     * -1 if it does not exist.
     */
    int unBlockThread(int tid);

    /**
     * @param tid: the tid of the thread we want to check if is block.
     * @return true is it exists and blocked, false otherwise.
     */
    bool isThreadBlocked(int tid);

    /**
     * cause the thread with the supplied tid (if exists) to sleep.
     * @param tid: the tid of the thread we want to put to sleep.
     */
    void putThreadToSleep(int tid);

    /**
     * @param tid: the tid of the thread we want to wake.
     * @return 0 if the thread exists and we succeed on waking it,
     * -1 if it does not exist.
     */
    int wakeThread(int tid);

    /**
     * @param tid: the tid of the thread we want to check if asleep.
     * @return true if the thread with tid exists and asleep, false otherwise.
     */
    bool isThreadAsleep(int tid);

    /**
     * @param tid: the tid of a thread.
     * @return the num of quants of the thread of the supplied tid is exists,
     * -1 otherwise.
     */
    int getThreadQuants(int tid);

    /**
     * switches the context of the
     * @param currTid : the tid of the thread we want to switch from
     * @param nextTid : the tid of the thread we want to switch to.
     */
    void switchContext(int currTid, int nextTid);
};

#endif //OSEX2_HANDLER_H
