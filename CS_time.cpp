/******************************************************************************
* IP_ledge_detect.cpp
* This file contains functions that deal with detecting ledges.
*
******************************************************************************/

/////////////////////////// STANDARD INCLUDES  ////////////////////////////////
#include <time.h>
#include <chrono>
#include <thread>

/////////////////////////// PROJECT INCLUDES   ////////////////////////////////
#include "CS_time.hpp"

/////////////////////////// GLOBAL VARIABLES   ////////////////////////////////
static clock_t begin_time;

/////////////////////////// EXPORTED FUNCTIONS ////////////////////////////////
void start_timer(void)
{
    begin_time = clock();
    return;
}

float get_elapsed_time(void)
{
    return (float(clock() - begin_time) / CLOCKS_PER_SEC);
}

void sleep_for_milliseconds(int sleep_milli)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
}
