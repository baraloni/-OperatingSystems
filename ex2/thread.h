#ifndef TEMPEX2_THREAD_H
#define TEMPEX2_THREAD_H

#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>
#include <cstring>

typedef unsigned long address_t;

/**
 * This class is a "ticket" which saves on it the thread's information. It is supposed to be
 * somehow similar to a PCB entry, but for threads.
 */
class thread
{
    char* _stack;
    int _quants; // holds the number of quantums this thread spent as RUNNING.
    bool _isBlocked;
    bool _isSleeping;

    /** translates the address of a variable, Used as a black box in our code.
     * @param addr the address of a variable.
     * @return the translation of the address of the variable.
     */
    address_t translateAddress(address_t addr);

public:
    sigjmp_buf _env;

    /**
     * Creates a new thread object.
     * @param env : the address of the thread's environment.
     */
    explicit thread();

    /**
     * destructs this thread object.
     */
    ~thread();


    /**
     * sets up the thread context
     * @param f : The function the thread should execute.
     * @param stackSize: The size of the thread's size.
     * @return 0 on success. if failed: prints the error and returns -1.
     */
    int setupThread(void(*f)(), int stackSize);

    /**
     * Updates the _setBlocked parameter.
     * @param isBlocked
     */
    void setBlocked(bool isBlocked);

    /**
     * Returns True iff the thread is blocked.
     * @return
     */
    bool getBlocked();

    /**
     * Updates the _setSleep parameter.
     * @param isSleeping
     */
    void setSleep(bool isSleeping);

    /**
     * Return True iff the thread is sleeping.
     * @return
     */
    bool getSleep();

    /**
     * Returns the number of quantums in which the thread had been active.
     * @return
     */
    int getQuants();

    /**
     * Increments the value of _quants in 1.
     */
    void updateQuants();


};


#endif //TEMPEX2_THREAD_H
