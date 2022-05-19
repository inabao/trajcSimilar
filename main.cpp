#include <iostream>
#include "distance.h"
#include "utils.h"
#include "experiment.h"
using namespace std;



int main() {
//     数据处理
//     file2paths(R"(E:\project\work\Xian_data\gps_20161001)", R"(E:\project\work\Xian_data\trajectory\tra_20161001)", 666);


    // 生成训练集
//    auto paths = readfile(datasource);
//    vector<int> querys;
//    for (int i = 0; i < 1; ++i) {
//        for (int j = 0; j < 100; ++j) {
//            querys.push_back(i * 100 + j);
//        }
//        cout << i << endl;
//        findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 1);
//        findMultiMostSimilar(paths, querys, "pss", filepath, 1);
//        findMultiMostSimilar(paths, querys, "pos", filepath, 1);
//        querys.clear();
//    }

//    auto paths = readfile(R"(E:\project\work\xian_data\trajectory\tra_20161001)");
//    path p1 = paths[8];
//    int i = 0;
////        path p2 = paths[8];
//    for (auto & p2 : paths) {
//        if (p2.size() < 10) continue;
//        cout << i++ << "  " << p1.size() << "  " << p2.size() << endl;
////        showResult("efficientAlgorithm", p1, p2);
//        showResult("exactS", p1, p2);
////        showResult("pos", p1, p2);
////        showResult("pss", p1, p2);
//    }




//    char targetString[1024];
//    vector<string> datas{"xian"};
//    for (const auto &item : datas) {
//        dataType = item;
//        cout << item << endl;
//        snprintf(targetString, sizeof targetString, datasource, item.c_str());
//        string tmp(targetString);
//        dataLengthFilter(targetString, 200, 300, 2000);
//        dataLengthFilter(targetString, 300, 400, 2000);
//        dataLengthFilter(targetString, 400, 500, 2000);
//        dataLengthFilter(targetString, 500, 600, 2000);
//        dataLengthFilter(targetString, 600, 700, 2000);
//        cout << endl;
//        cout << endl;
//    }


//    varyLength(4, 8, "porto");
//    varyLength(8, 12, "porto");
//    varyLength(12, 16, "porto");
//    varyLength(16, 20, "porto");
//    varyLength(20, 40, "chengdu");
//    varyLength(40, 60, "chengdu");
//    varyLength(60, 80, "chengdu");
//    varyLength(80, 100, "chengdu");
//    varyLength(100, 120, "chengdu");
//    varyLength(80, 100, "xian");
//    varyLength(100, 120, "xian");
//    varyLength(120, 140, "xian");
//    varyLength(140, 160, "xian");
//    varyLength(160, 180, "xian");

//    varyQuerySize(20);
//    varyQuerySize(40);
//    varyQuerySize(60);
//    varyQuerySize(80);
//    varyQuerySize(100);
//    varyQuerySize(120);
//    varyQuerySize(140);
//    varyQuerySize(160);
//    varyQuerySize(180);
//    varyQuerySize(200);


//    varyDataSize(20000);
//    varyDataSize(30000);
//    varyDataSize(40000);
//    varyDataSize(50000);
//    varyDataSize(60000);
//    varyDataSize(70000);

//    varyDataLength(200, 300);
//    varyDataLength(300, 400);
//    varyDataLength(400, 500);
//    varyDataLength(500, 600);
//    varyDataLength(600, 700);

//     varyGridSize();
//     varyKeyNum();
//     varyRate();


//    auto paths = readfile(R"(E:\project\work\xian_data\trajectory\tra_20161001)");
//    vector<int> querys{649};
//    findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 1);
//    findMostSimilar(paths, 649, "efficientAlgorithm", filepath, 2);

    string s1 = "aabccd";
    string s2 = "bacaabaccdda";
    auto p1 = str2path(s1);
    auto p2 = str2path(s2);
//    showResult("efficientAlgorithm", p1, p2);
    showResult("exactS", p1, p2);
//    showResult("pss", p1, p2);

//    string s1 = "bbaacbabc";
//    string s2 = "bacaabacc";
//    auto p1 = str2path(s1);
//    auto p2 = str2path(s2);
//    cout << dtwDistance(p1, p2, 0, p2.size());

    return 0;
}
