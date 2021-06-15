#ifndef EX2_VIRTUAL_TIMER_H
#define EX2_VIRTUAL_TIMER_H

#include <sys/time.h>

class virtual_timer {
    int _quantum;
    struct itimerval _timer;

public:
    /**
     * Creates a virtual timer that counts a quantum each time.
     * @param quantum: The number of micro seconds the timer should count.
     */
    explicit virtual_timer(int quantum);

    /**
     * Starts the timer to run quantum microseconds.
     * @return -1 in case of a system error.
     */
    int start();
};


#endif //EX2_VIRTUAL_TIMER_H
