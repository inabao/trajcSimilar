//
// Created by 86173 on 2022/2/8.
//

#ifndef TRAJCSIMILAR_EXPERIMENT_H
#define TRAJCSIMILAR_EXPERIMENT_H

#include <sys/time.h>
#include "mostSimilar.h"
void showResult(const string& algorithm, const path& p1, const path& p2);
void findMostSimilar(const vector<path>& paths, int query, const string& algorithm, const string& targetFile, int limit=1);
void findMultiMostSimilar(const vector<path>& paths, vector<int> querys, const string& algorithm, const string& targetFile, int limit);
#endif //TRAJCSIMILAR_EXPERIMENT_H
