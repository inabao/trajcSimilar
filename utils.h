//
// Created by 86173 on 2022/1/27.
//

#ifndef TRAJCSIMILAR_UTILS_H
#define TRAJCSIMILAR_UTILS_H
#include <fstream>
#include <algorithm>
#include "distance.h"
#include "iostream"
#include "map"
#include <sstream>

using namespace std;

path str2path(const string &s);

vector<path> readfile(const string& filename);
void file2paths(const string& filename, const string& target, int bound);
vector<string> split(string str, string pattern);
void paths2file(const string& filename, vector<path>);
#endif //TRAJCSIMILAR_UTILS_H
