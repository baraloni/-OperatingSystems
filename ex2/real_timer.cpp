#include "real_timer.h"
static const int CONVERTION_CONST_MSEC_SEC = 1000000;

int real_timer::start(int expTime) {

    // Zero timer:
    _timer.it_value.tv_sec = 0;
    _timer.it_value.tv_usec = 0;
    if (setitimer (ITIMER_REAL, &_timer, nullptr)) {
        return -1;
    }

    // Set Timer
    int secondsPart = expTime / CONVERTION_CONST_MSEC_SEC;   // down round.
    int microSecondsPart = expTime - (secondsPart * CONVERTION_CONST_MSEC_SEC);
    _timer.it_value.tv_sec = secondsPart;
    _timer.it_value.tv_usec = microSecondsPart;

    // Start timer:
    if (setitimer (ITIMER_REAL, &_timer, nullptr)) {
        return -1;
    }
    return 0;
}
