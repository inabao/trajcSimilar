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
const static vector<double> x_range = {108.89, 109.01};
const static vector<double> y_range = {34.19, 34.29};


static bool generateResult = false;

static double MaxSimilar = 100000000000;

static string filepath = R"(E:\project\work\trajcSimilar\result\result\)";
static const char *datasource = R"(E:\project\work\%s_data\trajectory\tra_20161001)";


const static pair<double, double> nullPoint = pair<double, double>{-1000,-1000};
const static pair<double, double> centerPoint = pair<double, double>{34.44, 109.95}; // 西安
#endif //TRAJCSIMILAR_CONSTANT_H
