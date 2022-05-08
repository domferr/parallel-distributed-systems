//
// Created by domenico on 07/05/22.
//

#define LOGGING 0
#include "../utils/logger/logger.h"
#include <iostream>
#include <chrono>
#include "map.h"
#include "../utils/utimer/utimer.h"

#define VECTOR_SIZE 64
#define ACTIVE_WAIT_MS 2000

void active_wait(long ms) {
    auto start_ms = std::chrono::system_clock::now();
    long elapsed = 0;
    while(elapsed < ms) {
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - start_ms).count();
    }
}

void vector_fill_randomly(std::vector<float> &vec) {
    auto divider = (float) (rand() / 2);
    for (size_t i = 0; i < vec.size(); ++i) {
        vec[i] = (float) rand() / divider;
    }
}

void vector_println(const std::vector<float> &vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "": ", ");
    }
    std::cout << "]" << std::endl;
}

/**
 * Provide a vector<float> map(vector<float>v, int mode, function<float(float)> f, int pardegree) computing in parallel
 * (using C++ threads or asyncs) the map(f) over v. Mode is 0 (block) or 1 (cyclic) scheduling.
 */
int main(int argc, char* argv[]) {
    if (argc != 3) { // assignment2 <mode> <pardegree>
        std::cout << "Usage: " << argv[0] << " <mode 0 or 1> <pardegree>" << std::endl;
        return 0;
    }
    int mode = strtol(argv[1], nullptr, 10);
    size_t pardegree = strtol(argv[2], nullptr, 10);

    auto seed = time(nullptr);
    std::cout << "Seed: " << seed << std::endl;
    srand(seed);

    std::vector<float> vec(VECTOR_SIZE);
    vector_fill_randomly(vec);
    std::cout << "Random vector of " << vec.size() << " elements: ";
    vector_println(vec);

    auto double_fun = [](float v, long active_wait_ms = ACTIVE_WAIT_MS) {
        active_wait(active_wait_ms);
        return v*v;
    };

    std::vector<float> res;
    {
        utimer tim("Map");
        res = map(vec, mode, double_fun, pardegree);
    }

    // Check if the result is correct
    if (vec.size() != res.size()) {
        log_error("Error: Resulting vector has different size");
    }

    for (size_t i = 0; i < vec.size(); ++i) {
        auto good_result = double_fun(vec[i], 0);
        if (i < res.size() && good_result != res[i])
            log_error("Error: the value in position ", i, " must be ", good_result, " but it is ", res[i]);
    }

    return 0;
}