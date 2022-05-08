//
// Created by domenico on 07/05/22.
//

#ifndef PARALLEL_DISTRIBUTED_SYSTEMS_MAP_H
#define PARALLEL_DISTRIBUTED_SYSTEMS_MAP_H

#include <vector>
#include <functional>

/*
 * map(f) over v with parallelism degree pardegree.
 *
 * @param v vector of element on which the given function will be applied
 * @param mode 0 (block) or 1 (cyclic) scheduling
 * @param f function to be applied to each element
 * @param pardegree the desired parallelism degree.
 * @return the resulting vector
 */
std::vector<float> map(const std::vector<float> &v, int mode, const std::function<float(float)>& f, size_t pardegree);

#endif //PARALLEL_DISTRIBUTED_SYSTEMS_MAP_H
