//
// Created by Szymon on 2023-04-22.
//

#include "Timer.h"

Timer::Timer() {
    QueryPerformanceFrequency(&freq);
}

//starts the count/ rozpoczyna odliczanie
void Timer::start() {
    QueryPerformanceCounter(&start_time);
}

//stops thge count/ konczy odliczanie
void Timer::stop() {
    QueryPerformanceCounter(&end_time);
}

//returns the time between the start and stop in seconds
long long Timer::secs() const {
    QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
    return (end_time.QuadPart - start_time.QuadPart) / freq.QuadPart;
}

//returns the time between the start and stop in miliseconds
long long Timer::milisecs() const {
    QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
    return (end_time.QuadPart - start_time.QuadPart) * 1000 / freq.QuadPart;
}

//returns the time between the start and stop in microseconds
long long Timer::microsecs() const {
    QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
    return (end_time.QuadPart - start_time.QuadPart) * 1000000 / freq.QuadPart;
}

//returns the time between the start and stop in nanoseconds
long long Timer::nanosecs() const {
    QueryPerformanceFrequency((LARGE_INTEGER *) &freq);
    return (end_time.QuadPart - start_time.QuadPart) * 1000000000 / freq.QuadPart;
}

void Timer::time_show() const {
    std::cout << secs() << "s ";
    std::cout << milisecs() - secs() * 1000 << "ms ";
    std::cout << microsecs() - secs() * 1000000 - milisecs() * 1000 << "us ";
    std::cout << nanosecs() - secs() * 1000000000 - milisecs() * 1000000 - microsecs() * 1000;
}

//show the timespan/ pokazuje czas ktory uplynal
void Timer::to_time(const long long &nano) {
    int s = nano / 1000000000;
    int ms = nano / 1000000 - s * 1000;
    int us = nano / 1000 - s * 1000000 - ms * 1000;
    int ns = nano - s * 1000000000 - ms * 1000000 - us * 1000;
    std::cout << s << "s " << ms << "ms " << us << "us " << ns << "ns\n";
}

