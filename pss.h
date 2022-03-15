//
// Created by 86173 on 2022/2/7.
//

#ifndef TRAJCSIMILAR_PSS_H
#define TRAJCSIMILAR_PSS_H

#include "distance.h"
#include "istream"

using namespace std;
subResult pss(const path& p1, const path& p2);
subResult pos(const path& p1, const path& p2);

extern string matricsType;
extern string pruningType;
extern string gatherType;
extern string dataType;

#endif //TRAJCSIMILAR_PSS_H
