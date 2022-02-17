//
// Created by 86173 on 2022/2/8.
//

#include "experiment.h"

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

    printf("algorithm:%-25sstart:%-10dend:%-10dscore:%-20lfcost:%15d\n",
           algorithm.c_str(),
           result.first.first,
           result.first.second,
           result.second,
           time_end - time_start
           );
}
void findMostSimilar(const vector<path>& paths, int query, const string& algorithm, const string& targetFile, int limit) {
    auto time_start = nowTime();
    auto results = mostSimilar(paths, query, algorithm, limit);
    auto time_end = nowTime();

    ofstream ofs(targetFile + to_string(time_start) + "findMostSimilar");
    ofs << "algorithm:" << algorithm << " queryLength:" << paths[query].size() <<  " datasize:" <<
          paths.size() << " score:" << exactS(paths[query], results[0]).second << " cost:" << time_end - time_start;
    paths2file(targetFile + "result.txt", results);
}

void findMultiMostSimilar(const vector<path>& paths, vector<int> querys, const string& algorithm, const string& targetFile, int limit) {
    auto time_start = nowTime();
    auto results = multiSimilar(paths, querys, algorithm, limit);
    auto time_end = nowTime();

    ofstream ofs(targetFile + to_string(time_start) + "findMostSimilar");
    ofs << "algorithm:" << algorithm << " queryLength:" << querys.size() <<  " datasize:" <<
    paths.size() <<" cost:" << time_end - time_start;
    for (const auto &item : querys) {
        paths2file(targetFile + to_string(item) + "_result.txt", results[item]);
    }
}


