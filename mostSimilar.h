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

subResult execute(const string & algorithm, const path& p1, const path& p2);
vector<path> mostSimilar(vector<path> paths, int query, const string& algorithm, int limit);
map<int, vector<path>> multiSimilar(const vector<path>& paths, const vector<int>& querys, const string& algorithm, int limit);

map<int, vector<path>> multiSimilarNaive(const vector<path>& paths, const vector<int>& querys, const string& algorithm, int limit);
#endif //TRAJCSIMILAR_MOSTSIMILAR_H
