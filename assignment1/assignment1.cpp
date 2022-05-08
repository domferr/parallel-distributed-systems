/**
 * Evaluate overhead needed to start/join a thread and to start an async (launch::async policy) and get the result of
 * the computed future. Measures should be taken as averages of a large number of events. Possibly, measure times on
 * your machine AND on the remote virtual machine.
 */

#include <unistd.h>
#include <iostream>
#include <thread>
#include <future>
#include "../utils/utimer/utimer.h"

void with_threads(void (*fun) (), int repetitions) {
    long sum = 0;
    long max = -1;
    long min = -1;

    int i = 0;
    while(i < repetitions) {
        {
            //utimer tim("Start and join a thread");
            START(st);
            auto t1 = std::thread(fun);

            t1.join();
            STOP(st, elapsed);
            if (elapsed > max) max = elapsed;
            if (elapsed < min || min == -1) min = elapsed;
            sum += elapsed;

            std::cout << "Computed in " << elapsed << " usec" << std::endl;
        }
        i++;
    }

    sum = sum - max - min;
    std::cout << "Start and join a thread. Average: " << (sum / (repetitions - 2)) << std::endl;
}

void with_asyncs(void (*fun) (), int repetitions) {
    long sum = 0;
    long max = -1;
    long min = -1;

    int i = 0;
    while(i < repetitions) {
        {
            //utimer tim("Start and get the result of an async");
            START(st);
            auto future = std::async(std::launch::async, fun);

            future.get();
            STOP(st, elapsed);
            if (elapsed > max) max = elapsed;
            if (elapsed < min || min == -1) min = elapsed;
            sum += elapsed;

            std::cout << "Computed in " << elapsed << " usec" << std::endl;
        }
        i++;
    }

    sum = sum - max - min;
    std::cout << "Start and get the result of an async. Average: " << (sum / (repetitions - 2)) << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) std::cout << "Usage: " << argv[0] << " <repetitions> <0 for threads, 1 for asyncs>" << std::endl;

    int repeat = strtol(argv[1], nullptr, 10);
    int choice = strtol(argv[2], nullptr, 10);
    auto fun = [] () {
        //sleep(2);
        for (int i = 0; i < 100000; ++i) {

        }
    };

    if (choice == 0)
        with_threads(fun, repeat);
    else if (choice == 1)
        with_asyncs(fun, repeat);

    return 0;
}
