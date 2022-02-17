//
// Created by 86173 on 2022/2/3.
//

#ifndef TRAJCSIMILAR_CONSTANT_H
#define TRAJCSIMILAR_CONSTANT_H
#include "distance.h"
using namespace std;
typedef pair<double,double> point;
typedef vector<point> path;
typedef pair<pair<int, int>, double> subResult;

static string matricsType = "edr";
static string pruningType = "pointprune";
static string gatherType = "gridbase";
static double MaxSimilar = 100000000000;
static pair<double, double> nullPoint = pair<double, double>{-1000,-1000};
static pair<double, double> centerPoint = pair<double, double>{108.95, 34.24}; // 西安
#endif //TRAJCSIMILAR_CONSTANT_H
