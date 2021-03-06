//
// Created by Domenico on 25/04/2022.
//

#ifndef UTIMER_H
#define UTIMER_H

#include <iostream>
#include <chrono>
#include <thread>

#define START(timename) auto timename = std::chrono::system_clock::now();
#define STOP(timename,elapsed)  auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - timename).count();

class utimer {
    std::chrono::system_clock::time_point start;
    std::chrono::system_clock::time_point stop;
    std::string message;
    using usecs = std::chrono::microseconds;
    using msecs = std::chrono::milliseconds;

private:
    long * us_elapsed;

public:
    utimer(const std::string m);
    utimer(const std::string m, long * us);
    ~utimer();
};

#endif //UTIMER_H
