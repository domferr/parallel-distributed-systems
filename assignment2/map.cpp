//
// Created by domenico on 07/05/22.
//

#include <thread>
#include "map.h"
#define LOGGING 0
#include "../utils/logger/logger.h"

#define MODE_BLOCK  0
#define MODE_CYCLIC 1

void th_block(size_t th_id, const std::vector<float> &input, std::vector<float> &output, const std::function<float(float)>& f, size_t start_ind, size_t end_ind) {
    log_info("Thread ", th_id, ": compute f on block [", start_ind, ", ", end_ind, "]");
    for (size_t i = start_ind; i <= end_ind; ++i) {
        output[i] = f(input[i]);
    }
}

void th_cyclic(size_t th_id, const std::vector<float> &input, std::vector<float> &output, const std::function<float(float)>& f, size_t start, size_t pardegree) {
    size_t pos = start;
    while (pos < input.size()) {
        log_info("Thread ", th_id, ": compute f on element in position ", pos);
        output[pos] = f(input[pos]);

        pos += pardegree;
    }
}

std::vector<float> map(const std::vector<float> &v, int mode, const std::function<float(float)>& f, size_t pardegree) {
    std::thread th[pardegree];
    std::vector<float> result(v.size());

    if (mode == MODE_BLOCK) { // block scheduling
        if (pardegree > v.size()) pardegree = v.size(); // do not use more threads than the number of elements

        size_t blocksize = v.size() / pardegree, start, end;
        for (size_t i = 0; i < pardegree; ++i) {
            start = blocksize * i;
            if (i + 1 == v.size() / blocksize) end = v.size() - 1;
            else end = start + blocksize - 1;

            th[i] = std::thread(th_block, i, v, std::ref(result), f, start, end);
        }
    } else {
        for (size_t i = 0; i < pardegree; ++i) {
            th[i] = std::thread(th_cyclic, i, v, std::ref(result), f, i, pardegree);
        }
    }

    for (size_t i = 0; i < pardegree; ++i) {
        th[i].join();
        log_info("Joined thread ", i);
    }

    return result;
}