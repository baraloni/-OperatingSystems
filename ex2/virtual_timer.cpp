#include "virtual_timer.h"
static const int CONVERTION_CONST_MSEC_SEC = 1000000;

virtual_timer::virtual_timer(int quantum): _quantum(quantum), _timer(){}

int virtual_timer::start() {
    // Zero timer:
    _timer.it_value.tv_sec = 0;
    _timer.it_value.tv_usec = 0;
    if (setitimer (ITIMER_VIRTUAL, &_timer, nullptr)) {
        return -1;
    }

    // Set timer:
    int secondsPart = _quantum / CONVERTION_CONST_MSEC_SEC;   // down round.
    int microSecondsPart = _quantum - (secondsPart * CONVERTION_CONST_MSEC_SEC);

    _timer.it_value.tv_sec = secondsPart;
    _timer.it_value.tv_usec = microSecondsPart;

    // Run timer:
    if (setitimer (ITIMER_VIRTUAL, &_timer, nullptr)) {
        return -1;
    }
    return 0;
}
