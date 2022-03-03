#include <iostream>
#include "distance.h"
#include "utils.h"
#include "experiment.h"
using namespace std;



int main() {
//     data preprocessing
//     file2paths(R"(E:\project\work\Xian_data\gps_20161001)", R"(E:\project\work\Xian_data\trajectory\tra_20161001)", 666);


//    auto paths = readfile(R"(E:\project\work\Xian_data\trajectory\tra_20161001)");
//    path p1 = paths[3];
//    int i = 0;
////    path p2 = paths[43];
//    for (auto & p2 : paths) {
//        if (p2.size() < 10) continue;
//        cout << i++ << "  " << p1.size() << "  " << p2.size() << endl;
//        showResult("efficientAlgorithm", p1, p2);
//        showResult("exactS", p1, p2);
//        showResult("pss", p1, p2);
//    }


    auto paths = readfile(datasource);
    vector<int> querys{251};
    findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 50);

//    findMostSimilar(paths, 649, "efficientAlgorithm", filepath, 2);

//    string s1 = "aabccd";
//    string s2 = "bacaabaccdda";
//    auto p1 = str2path(s1);
//    auto p2 = str2path(s2);
//    showResult("efficientAlgorithm", p1, p2);
//    showResult("exactS", p1, p2);
//    showResult("pss", p1, p2);

//    string s1 = "bbaacbabc";
//    string s2 = "bacaabacc";
//    auto p1 = str2path(s1);
//    auto p2 = str2path(s2);
//    cout << dtwDistance(p1, p2, 0, p2.size());

    return 0;
}
