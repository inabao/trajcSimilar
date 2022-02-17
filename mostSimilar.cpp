//
// Created by 86173 on 2022/2/16.
//

#include "mostSimilar.h"

subResult execute(const string & algorithm, const path& p1, const path& p2){
    subResult result;
    if (algorithm == "efficientAlgorithm") {
        result = efficientAlgorithm(p1, p2);
    } else if (algorithm == "exactS") {
        result = exactS(p1, p2);
    } else if (algorithm == "pss") {
        result = pss(p1, p2);
    }
    return result;
}





vector<path> mostSimilarNonePruning(vector<path> paths, int query, const string& algorithm, int limit) {
    path queryPath = paths[query];
    subResult empty;
    empty.second = 100000000000;
    vector<subResult> record;
    vector<int> pathId;
    vector<path> results;

    for (int i = 0; i < paths.size(); ++i) {
        if (i != query && paths[i].size() > queryPath.size()) {
            auto res = execute(algorithm, queryPath, paths[i]);
            bool flag = false;
            for (int j = 0; j < record.size(); ++j) {
                if (record[j].second > res.second) {
                    record.insert(record.begin() + j, res);
                    pathId.insert(pathId.begin() + j, i);
                    flag = true;
                    break;
                }
            }
            if (!flag && record.size() < limit) {
                pathId.push_back(i);
                record.push_back(res);
            }
        }
    }
    for (int i = 0; i < limit; ++i) {
        path tmp(paths[pathId[i]].begin() + record[i].first.first, paths[pathId[i]].begin() + record[i].first.second + 1);
        results.push_back(tmp);
        results.push_back(paths[pathId[i]]);
    }
    results.push_back(queryPath);
    return results;
}

double lowBoundEstimate(vector<point> points, const path& p, int skip) {
    double result[points.size()];
    for (int i = 0; i < points.size(); ++i) {
        result[i] = MaxSimilar;
    }
    for (int i = 0; i < p.size(); i += skip) {
        for (int j = 0; j < points.size(); j ++) {
            if (matricsType == "dtw") {
                result[j] = min(result[j], pointDistance(points[j], p[i]));
            } else {
                result[j] = min(result[j], distance(points[j], p[i]));
            }
        }
    }
    double sum = 0;
    for (int i = 0; i < points.size(); ++i) {
        sum += result[i];
    }
    return sum / points.size();
}


vector<path> mostSimilarPointPrune(vector<path> paths, int query, const string& algorithm, int limit) {
    path queryPath = paths[query];
    subResult empty;
    empty.second = MaxSimilar;
    vector<subResult> record;
    vector<int> pathId;
    vector<path> results;
    double lowerBound = MaxSimilar;
    vector<point> points;
    points.push_back(queryPath[queryPath.size() / 4]);
    points.push_back(queryPath[2 * queryPath.size() / 4]);
    points.push_back(queryPath[3 * queryPath.size() / 4]);
    for (int i = 0; i < paths.size(); ++i) {
        int b = queryPath.size() * lowBoundEstimate(points, paths[i], 2);
        if (i != query && paths[i].size() > queryPath.size() && lowerBound > b) {
            auto res = execute(algorithm, queryPath, paths[i]);
            bool flag = false;
            for (int j = 0; j < record.size(); ++j) {
                if (record[j].second > res.second) {

                    record.insert(record.begin() + j, res);
                    pathId.insert(pathId.begin() + j, i);
                    flag = true;
                    break;
                }
            }
            if (!flag && record.size() < limit) {
                pathId.push_back(i);
                record.push_back(res);
            }
            lowerBound = record[min((int)record.size(), limit) - 1].second;
        }
    }
    for (int i = 0; i < limit; ++i) {
        path tmp(paths[pathId[i]].begin() + record[i].first.first, paths[pathId[i]].begin() + record[i].first.second + 1);
        results.push_back(tmp);
        results.push_back(paths[pathId[i]]);
    }
    results.push_back(queryPath);
    return results;
}



vector<path> mostSimilar(vector<path> paths, int query, const string& algorithm, int limit) {
    if (pruningType == "none") {
        return mostSimilarNonePruning(std::move(paths), query, algorithm, limit);
    } else if (pruningType == "pointprune") {
        return mostSimilarPointPrune(std::move(paths), query, algorithm, limit);
    }
    return {};
}

map<int, bool> multiLowBoundEstimate(map<int, vector<point>> points, const path& p, const vector<path>& paths,map<int, double> &lowerBounds, int skip) {
    map<int, vector<double>> result;
    for (const auto &item : points) {
        result[item.first] = vector<double>(3, MaxSimilar);
    }
    for (int i = 0; i < p.size(); i += skip) {
        for (auto & po : points) {
            for (int k = 0; k < 3; ++k) {
                if (matricsType == "dtw") {
                    result[po.first][k] = min(result[po.first][k], pointDistance(po.second[k], p[i]));
                } else {
                    result[po.first][k] = min(result[po.first][k], distance(po.second[k], p[i]));
                }
            }
        }
    }
    map<int, bool> search;
    for (const auto &item : result) {
        search[item.first] = lowerBounds[item.first] > (accumulate(begin(item.second), end(item.second), 0.0) / item.second.size()) * paths[item.first].size();
    }
    return search;
}




map<int, bool> multiLowBoundEstimateGridBase(map<int, vector<point>> points, const path& p, const vector<path>& paths,map<int, double> &lowerBounds, int skip) {
    map<int, vector<double>> result;
    for (const auto &item : points) {
        result[item.first] = vector<double>(3, MaxSimilar);
    }
    for (int i = 0; i < p.size(); i += skip) {
        for (auto & po : points) {
            for (int k = 0; k < 3; ++k) {
                if (matricsType == "dtw") {
                    result[po.first][k] = min(result[po.first][k], pointDistance(po.second[k], p[i]));
                } else {
                    result[po.first][k] = min(result[po.first][k], distance(po.second[k], p[i]));
                }
            }
        }
    }
    map<int, bool> search;
    for (const auto &item : result) {
        search[item.first] = lowerBounds[item.first] > (accumulate(begin(item.second), end(item.second), 0.0) / item.second.size()) * paths[item.first].size();
    }
    return search;
}



map<int, vector<path>> multiSimilar(const vector<path>& paths, const vector<int>& querys, const string &algorithm, int limit) {
    subResult empty;
    empty.second = MaxSimilar;
    map<int, vector<subResult>> record;
    map<int, vector<int>> pathId;
    map<int, vector<path>> results;
    map<int, double> lowerBound;
    map<int, vector<point>> points;
    for (const auto &item : querys) {
        auto queryPath = paths[item];
        points[item].push_back(paths[item][queryPath.size() / 4]);
        points[item].push_back(paths[item][2 * queryPath.size() / 4]);
        points[item].push_back(queryPath[3 * queryPath.size() / 4]);
        lowerBound[item] = MaxSimilar;
    }

    for (int i = 0; i < paths.size(); ++i) {
        auto multiLowBounds = multiLowBoundEstimate(points, paths[i], paths, lowerBound, 2);
        for (const auto &query : querys) {
            auto queryPath = paths[query];
            if (i != query && paths[i].size() > queryPath.size() && multiLowBounds[query]) {
                auto res = execute(algorithm, queryPath, paths[i]);
                bool flag = false;
                for (int j = 0; j < record[query].size(); ++j) {
                    if (record[query][j].second > res.second) {
                        record[query].insert(record[query].begin() + j, res);
                        pathId[query].insert(pathId[query].begin() + j, i);
                        flag = true;
                        break;
                    }
                }
                if (!flag && record[query].size() < limit) {
                    pathId[query].push_back(i);
                    record[query].push_back(res);
                }
                lowerBound[query] = record[query][min((int)record[query].size(), limit) - 1].second;
            }

        }
    }
    for (const auto &query : querys) {
        for (int i = 0; i < limit; ++i) {
            path tmp(paths[pathId[query][i]].begin() + record[query][i].first.first, paths[pathId[query][i]].begin() + record[query][i].first.second + 1);
            results[query].push_back(tmp);
            results[query].push_back(paths[pathId[query][i]]);
        }
        results[query].push_back(paths[query]);
    }
    return results;
}

map<int, vector<path>>
multiSimilarNaive(const vector<path> &paths, const vector<int> &querys, const string &algorithm, int limit) {
    map<int, vector<path>> results;
    for (const auto &item : querys) {
        results[item] = mostSimilar(paths, item, algorithm, limit);
    }
    return {};
}
