#ifndef CLOCK_H
#define CLOCK_H

#include <stdint.h>
#include "include/var.h"


static inline uint64_t read_tsc() {
    uint32_t lo, hi;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

void wait_ticks(uint64_t ticks){
    uint64_t start = read_tsc();

    while(read_tsc()-start < ticks){
        __asm__ volatile("pause");
    }

}

void wait_ms(int ms){
    wait_ticks((uint64_t)ms*(uint64_t)tsc_ticks_per_ms);
}

#endif