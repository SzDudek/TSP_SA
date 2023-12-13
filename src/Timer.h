//
// Created by Szymon on 2023-04-22.
//

#ifndef PEA2_TIMER_H
#define PEA2_TIMER_H

#include <windows.h>
#include <iostream>
#include <ctime>

class Timer {
public:

    Timer();

    void start();

    void stop();

    long long secs() const;

    long long milisecs() const;

    long long microsecs() const;

    long long nanosecs() const;

    void time_show() const;

    static void to_time(const long long &nano);

private:

    LARGE_INTEGER start_time;
    LARGE_INTEGER end_time;
    LARGE_INTEGER freq;
};


#endif //PEA2_TIMER_H
