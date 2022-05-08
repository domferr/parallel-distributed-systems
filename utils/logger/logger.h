//
// Created by domenico on 07/05/22.
//

#ifndef PARALLEL_DISTRIBUTED_SYSTEMS_LOGGER_H
#define PARALLEL_DISTRIBUTED_SYSTEMS_LOGGER_H

#include <iostream>

#ifndef LOGGING
#define LOGGING 1
#endif
#if LOGGING
#define log_info(...) log(std::cout, -1, nullptr, __VA_ARGS__)
#define log_error(...) log(std::cerr, __LINE__, __FILE__, __VA_ARGS__)
#else
#define log_info(...)
#define log_error(...)
#endif

template <typename ...Args>
static void log(std::ostream &stream, int line, const char* fileName, Args&& ...args) {
    if (line >= 0 && fileName != nullptr) stream << fileName << "(" << line << ") : ";
    (stream << ... << std::forward<Args>(args)) << std::endl;

    //std::cout << stream.str().c_str();
}

#endif //PARALLEL_DISTRIBUTED_SYSTEMS_LOGGER_H
