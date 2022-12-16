#include "r2k_test/internal/r2k_timer.h"

r2k_timer_t r2k_timer_start() {
    r2k_timer_t timer;
    ftime(&timer.start);
    return timer;
}

r2k_milliseconds_t r2k_timer_stop(r2k_timer_t* timer) {
    ftime(&timer->end);
    int ms = 0;
    ms += (int) (1000.0 * (timer->end.time - timer->start.time)); // seconds
    ms +=  timer->end.millitm - timer->start.millitm; // milliseconds
    return (r2k_milliseconds_t) { .val = ms };
}
