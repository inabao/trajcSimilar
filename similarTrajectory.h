//
// Created by 86173 on 2022/1/27.
//

#ifndef TRAJCSIMILAR_SIMILARTRAJECTORY_H
#define TRAJCSIMILAR_SIMILARTRAJECTORY_H

#include "distance.h"

using namespace std;


double minSubTrajectory(const path& path1, const path& path2);
subResult efficientAlgorithm(const path& path1, const path& path2);
#endif //TRAJCSIMILAR_SIMILARTRAJECTORY_H
