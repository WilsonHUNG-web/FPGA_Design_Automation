#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>
#include <iostream>
#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

chrono::high_resolution_clock::time_point time_record()
{
    return chrono::high_resolution_clock::now();
}

double time_output(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time)
{
    return chrono::duration<double>(end_time - start_time).count();
}

unsigned int get_seed()
{
    // sleep(1);
    // unsigned int seed = time(NULL);
    // unsigned int seed = now();
    unsigned int seed = clock();
    // cout << "seed: " << seed << endl;
    return seed;
}

unsigned int seed_selector(string case_name)
{
    if (case_name == "case1")
        return 2751;
    else if (case_name == "case2")
        return 1514;
    else if (case_name == "case3")
        return 1058;
    else if (case_name == "case4")
        return 710;
    else if (case_name == "case5")
        return 781;
    else if (case_name == "case6")
        return 825;
    else
        return get_seed();
}

#endif