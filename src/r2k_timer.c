#include <r2k_test/internal/r2k_timer.h>

#define NS_PER_SECOND 1000000000

r2k_timer_t r2k_timer_start(void) {
    r2k_timer_t timer;
    clock_gettime(CLOCK_REALTIME, &timer.start);
    return timer;
}

r2k_milliseconds_t r2k_timer_stop(r2k_timer_t* timer) {
    clock_gettime(CLOCK_REALTIME, &timer->end);
    int ms = 0;
    ms += (int) ((timer->end.tv_sec - timer->start.tv_sec) * 1000.0); // seconds
    ms += (int) ((timer->end.tv_nsec - timer->start.tv_nsec) / 1000.0); // milliseconds
    return (r2k_milliseconds_t) { .value = ms };
}
