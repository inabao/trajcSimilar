//
// Created by 86173 on 2022/1/27.
//

#ifndef TRAJCSIMILAR_SIMILARTRAJECTORY_H
#define TRAJCSIMILAR_SIMILARTRAJECTORY_H

#include "distance.h"

using namespace std;


extern string matricsType;
extern string pruningType;
extern string gatherType;
extern string dataType;

//extern int maxLen;
//extern int minLen;
double minSubTrajectory(const path& path1, const path& path2);
subResult efficientAlgorithm(const path& path1, const path& path2);
#endif //TRAJCSIMILAR_SIMILARTRAJECTORY_H
