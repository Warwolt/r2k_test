#ifndef R2K_TIMER_H
#define R2K_TIMER_H

#include <sys/timeb.h>

typedef struct r2k_milliseconds {
    int value;
} r2k_milliseconds_t;

typedef struct r2k_timer {
    struct timeb start;
    struct timeb end;
} r2k_timer_t;

r2k_timer_t r2k_timer_start();
r2k_milliseconds_t r2k_timer_stop(r2k_timer_t* timer);

#endif // R2K_TIMER_H
