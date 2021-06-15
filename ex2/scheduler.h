
#ifndef TEMPEX2_SCHEDULER_H
#define TEMPEX2_SCHEDULER_H
#include <iostream>
#include <list>
#include <algorithm>
#include <cassert>

static const int MAIN_THREAD_ID = 0;

/**
 * A scheduler is an object that decides which thread should run next in case a context switch occurs.
 */
class scheduler
{
    std::list<int> _ready;
    int _running;

    /**
     * Pops the next thread to run from _ready and puts it in _running.
     */
    void _replaceRunning();

    /**
     * The treatment of blocking or termination from the scheduler's point of view is the same. This function updates
     * the internal state of the scheduler in either case.
     */
    void _handleBlockOrTermination(int tid);


public:

    /**
     * Initializes a new scheduler object with an empty ready queue and _running=0.
     */
    scheduler();

    /**
     * Decides who will be the next thread to run in the case the thread with tid got blocked. This method also
     * updates the scheduler's internal state according to the decision, and sets _running and ready accordingly.
     * @return the next tid to run.
     */
    int whosNextBlock(int tid);

    /**
     * Decides who will be the next thread to run in the case of a timeout. This method also
     * updates the scheduler's internal state according to the decision, and sets _running and ready accordingly.
     * @return the next tid to run.
     */
    int whosNextTimeout();

    /**
     * Decides who will be the next thread to run in the case the thread with this tid has terminated. This method also
     * updates the scheduler's internal state according to the decision, and sets _running and ready accordingly.
     * @return the next tid to run.
     */
    int whosNextTermination(int tid);

    /**
     * Decides who will be the next thread to run in the case the running should sleep. This method also
     * updates the scheduler's internal state according to the decision, and sets _running and ready accordingly.
     * @return the next tid to run.
     */
    int whosNextSleep();

    /**
     * Adds a thread to _ready if it's not already there.
     * @param tid
     */
     void addThread(int tid);

     /**
    * Returns which thread in is the CPU right now.
    * @return The id of the running thread.
    */
    int getRunning();

     /**
    * Prints the _ready list (for tests)
    */
    void printReady();

};


#endif //TEMPEX2_SCHEDULER_H
