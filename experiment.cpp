//
// Created by 86173 on 2022/2/8.
//

#include "experiment.h"

#include <utility>

long nowTime(){
    struct timeval curTime{};
    gettimeofday(&curTime, nullptr);
    long milli = curTime.tv_usec  + curTime.tv_sec * 1000 * 1000;
    return milli;
}

void showResult(const string& algorithm, const path& p1, const path& p2) {
    auto time_start = nowTime();
    auto result = execute(algorithm, p1, p2);
    auto time_end = nowTime();
    calScore(p1, p2, result.first.first, result.first.second + 1);
    printf("algorithm:%-20sstart:%-5dend:%-5dscore:%-10.4lfAR:%-10.4lfMR:%-10.4lfRR:%-10.4lfcost:%7d\n",
           algorithm.c_str(),
           result.first.first,
           result.first.second,
           result.second,
           AR,
           MR,
           RR,
           time_end - time_start
           );
}
void findMostSimilar(const vector<path>& paths, int query, const string& algorithm, const string& targetFile, int limit) {
    auto time_start = nowTime();
    auto results = mostSimilar(paths, query, algorithm, limit);
    auto time_end = nowTime();

    ofstream ofs(targetFile + to_string(time_start) + "findMostSimilar");
    ofs << "algorithm:" << algorithm << " queryLength:" << paths[query].size() <<  " datasize:" <<
          paths.size() << " score:" << efficientAlgorithm(paths[query], results[0]).second << " cost:" << time_end - time_start;
    paths2file(targetFile + "result.txt", results);
}

void findMultiMostSimilar(const vector<path>& paths, vector<int>& querys, const string& algorithm, string targetFile, int limit) {
    auto time_start = nowTime();
    auto results = multiSimilar(paths, querys, algorithm, limit);
    auto time_end = nowTime();
    ofstream ofs(targetFile + matricsType + "_" + dataType + "_" + algorithm + "_" + pruningType + "_" + to_string(minLen) + "_" +
                         to_string(maxLen));
    ofs << "matric:" << matricsType << ",dataset:" << dataType << ",pruningType:" << pruningType << ",algorithm:"
    << algorithm << ",queryLength:" << to_string(minLen) + "-" + to_string(maxLen) << ",querySize:" << querys.size() <<  ",datasize:" <<
    paths.size() <<",cost:" << time_end - time_start << endl;
    double score = 0;
    for (const auto &item : results) {
        double minScore = MaxSimilar;
        pair<vector<double>, subResult> tmp;
        for (const auto &_item : item.second) {
            if (minScore > _item.second.second.second) {
                minScore = _item.second.second.second;
                tmp = _item.second;
            }
            minScore = min(minScore, _item.second.second.second);
        }
        score += minScore;
        ofs << "pathId:" << item.first << "    score:" << minScore << "    AR:" << tmp.first[0] << "     MR:" << tmp.first[1]  << "    RR:" << tmp.first[2] << endl;
    }
    if (generateResult) {
        targetFile.append("similar_");
        targetFile.append(to_string(minLen));
        targetFile.append("_");
        targetFile.append(to_string(maxLen));
        targetFile.append("_");
        targetFile.append(matricsType);
        targetFile.append("_result.txt");
        for (const auto &item : results) {
            ids2file(targetFile, item.second, item.first);
        }
    }
}


void varyLength(int l, int r, string dataset) {
    minLen = l, maxLen = r;
    vector<int> querys;
    querys.reserve(100);
    for (int i = 0; i < 100; ++i) {
        querys.push_back(i);
    }
    vector<string> varyPrune{"gridbase", "none"};
    vector<string> metrics{"edr", "dtw", "erp"};
    char targetString[1024];
    dataType = dataset;
    for (const auto &pr : varyPrune) {
        pruningType = pr;
        for (const auto &item : metrics) {
            matricsType = item;
            snprintf(targetString, sizeof targetString, datasource, dataType.c_str());
            string tmp(targetString);
            auto paths = readfile(tmp);
            findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 1);
            findMultiMostSimilar(paths, querys, "pss", filepath, 1);
            findMultiMostSimilar(paths, querys, "pos", filepath, 1);
        }
    }
}

void varyDataLength(int l, int r) {
    string dataset = "xian";
    minLen = 80;
    maxLen = 100;


    vector<int> querys;
    querys.reserve(100);
    for (int i = 0; i < 100; ++i) {
        querys.push_back(i);
    }
    vector<string> varyPrune{"gridbase", "none"};
    vector<string> metrics{"edr", "dtw", "erp"};
    char targetString[1024];
    dataType = dataset;
    for (const auto &pr : varyPrune) {
        pruningType = pr;
        for (const auto &item : metrics) {
            matricsType = item;
            snprintf(targetString, sizeof targetString, datasource, dataType.c_str());
            string tmp(targetString);
            auto paths = readfile(tmp);
            findMultiMostSimilar(paths, querys, "efficientAlgorithm", filepath, 1);
            findMultiMostSimilar(paths, querys, "pss", filepath, 1);
            findMultiMostSimilar(paths, querys, "pos", filepath, 1);
        }
    }
}


