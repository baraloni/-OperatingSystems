#ifndef SLEEPING_THREADS_LIST_H
#define SLEEPING_THREADS_LIST_H

#include <deque>
#include <sys/time.h>

using namespace std;

struct wake_up_info {
    int id;
    timeval awaken_tv;
};

class SleepingThreadsList {

    deque<wake_up_info> sleeping_threads;

public:

    SleepingThreadsList();

    /*
     * Description: This method adds a new element to the list of sleeping
     * threads. It gets the thread's id, and the time when it needs to wake up.
     * The wakeup_tv is a struct timeval (as specified in <sys/time.h>) which
     * contains the number of seconds and microseconds since the Epoch.
     * The method keeps the list sorted by the threads' wake up time.
    */
    void add(int thread_id, timeval timestamp);

    /*
     * Description: This method removes the thread at the top of this list.
     * If the list is empty, it does nothing.
    */
    void pop();

    /*
     * Description: This method returns the information about the thread (id and time it needs to wake up)
     * at the top of this list without removing it from the list.
     * If the list is empty, it returns null.
    */
    wake_up_info* peek();

};

#endif
