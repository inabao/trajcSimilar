//
// Created by 86173 on 2022/1/27.
//

#ifndef TRAJCSIMILAR_EXACTS_H
#define TRAJCSIMILAR_EXACTS_H

#include "distance.h"
subResult exactS(const path& p1, const path& p2);
void calScore(const path& p1, const path& p2, int start, int end);

extern string matricsType;
extern string pruningType;
extern string gatherType;
extern string dataType;

extern double AR;
extern double RR;
extern double MR;
//extern int maxLen;
//extern int minLen;
#endif //TRAJCSIMILAR_EXACTS_H
