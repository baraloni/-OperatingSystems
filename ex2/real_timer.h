//
// Created by Jonathan Weiss on 2019-04-09.
//

#ifndef EX2_REALTIMER_H
#define EX2_REALTIMER_H
#include <sys/time.h>

class real_timer {
    struct itimerval _timer;

public:
    /**
     * Starts the timer to run expTime microseconds.
     * @param expTime: the number of microseconds the timer should count.
     * @return -1 in case of a system error.
     */
    int start(int expTime);

};


#endif //EX2_REALTIMER_H
