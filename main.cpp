#include <iostream>
#include "distance.h"
#include "utils.h"
#include "experiment.h"
using namespace std;

string filepath = R"(E:\project\work\trajcSimilar\result\result\)";
string datasource = R"(E:\project\work\Xian_data\trajectory\tra_20161001)";

int main() {
//     data preprocessing
//     file2paths(R"(E:\project\work\Xian_data\gps_20161001)", R"(E:\project\work\Xian_data\trajectory\tra_20161001)", 666);


//    auto paths = readfile(R"(E:\project\work\Xian_data\trajectory\tra_20161001)");
//    path p1 = paths[3];
//    for (auto & p2 : paths) {
//        if (p2.size() < 10) continue;
//        cout << p1.size() << "  " << p2.size() << endl;
//        showResult("efficientAlgorithm", p1, p2);
//        showResult("exactS", p1, p2);
//        showResult("pss", p1, p2);
//    }


    auto paths = readfile(datasource);
    vector<int> querys{649};
//    findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 2);
    findMostSimilar(paths, 649, "efficientAlgorithm", filepath, 2);

//    string s1 = "aabccd";
//    string s2 = "bacaabaccdda";
//    auto p1 = str2path(s1);
//    auto p2 = str2path(s2);
//    showResult("efficientAlgorithm", p1, p2);
//    showResult("exactS", p1, p2);
//    showResult("pss", p1, p2);

    return 0;
}
