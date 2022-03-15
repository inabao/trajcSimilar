//
// Created by 86173 on 2022/2/16.
//

#ifndef TRAJCSIMILAR_MOSTSIMILAR_H
#define TRAJCSIMILAR_MOSTSIMILAR_H


#include "istream"
#include "distance.h"
#include "utils.h"
#include "pss.h"
#include "exactS.h"
#include "similarTrajectory.h"

static double gridSize = 0.0001;
static double keyNum = 10;
static double fixRate = 0.6;

extern string matricsType;
extern string pruningType;
extern string gatherType;
extern string dataType;

extern int maxLen;
extern int minLen;

subResult execute(const string & algorithm, const path& p1, const path& p2);
vector<path> mostSimilar(vector<path> paths, int query, const string& algorithm, int limit);
map<int, map<int, subResult>> multiSimilar(const vector<path>& paths, vector<int> querys, const string& algorithm, int limit);

#endif //TRAJCSIMILAR_MOSTSIMILAR_H
