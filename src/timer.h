#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>

using namespace std;

chrono::high_resolution_clock::time_point time_record()
{
    return chrono::high_resolution_clock::now();
}

double time_output(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time)
{
    return chrono::duration<double>(end_time - start_time).count();
}

#endif