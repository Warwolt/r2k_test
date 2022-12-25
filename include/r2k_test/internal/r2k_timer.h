#ifndef R2K_TIMER_H
#define R2K_TIMER_H

#ifdef WIN32
#include <windows.h>
#else
#include <time.h>
#endif

typedef struct r2k_milliseconds {
    int value;
} r2k_milliseconds_t;

#ifdef WIN32
typedef struct r2k_timer {
    double pc_freq;
    __int64 start;
} r2k_timer_t;
#else
typedef struct r2k_timer {
    struct timespec start;
    struct timespec end;
} r2k_timer_t;
#endif

r2k_timer_t r2k_timer_start();
r2k_milliseconds_t r2k_timer_stop(r2k_timer_t* timer);

#endif // R2K_TIMER_H
