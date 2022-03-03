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
    for (int i = 0; i < keyNum; ++i) {
        points.push_back(queryPath[(i + 1) * queryPath.size() / (keyNum + 1)]);
    }
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
        result[item.first] = vector<double>(keyNum, MaxSimilar);
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
int x_size;
int y_size;

inline int gps2gridid(double x, double y) {
    int x_index = ceil((x - x_range[0]) / gridSize);
    int y_index = ceil((y - y_range[0]) / gridSize);
    return y_index * x_size + x_index;
}


map<int, vector<int>> initGrid(const map<int, vector<point>>& points) {
    map<int, vector<int>> pointGrid;
    x_size = ceil((x_range[1] - x_range[0]) / gridSize) + 2;
    y_size = ceil((y_range[1] - y_range[0]) / gridSize) + 2;
    for (const auto &item : points) {
        for (int i = 0; i < keyNum; ++i) {
            pointGrid[gps2gridid(item.second[i].second, item.second[i].first)].push_back(item.first);
        }
    }
    return pointGrid;
}




map<int, bool> multiLowBoundEstimateGridBase(map<int, vector<int>> pointGrid, const path& p, const vector<int>& querys, int skip) {
    map<int, int> count;
    for (int i = 0; i < p.size(); i += skip) {
        auto gridid = gps2gridid(p[i].second, p[i].first);
        for (int j = -1; j < 2; ++j) {
            for (int k = -1; k < 2; ++k) {
                int searchGridId = gridid + j * x_size + k;
                if (pointGrid.count(searchGridId) > 0) {
                    for (const auto &item : pointGrid[searchGridId]) {
                        count[item] ++;
                    }
                }
                pointGrid[searchGridId].clear();
            }
        }
    }
    map<int, bool> search;
    for (const auto &item : querys) {
        search[item] = count[item] > keyNum * fixRate;
    }
    return search;
}



map<int, map<int, subResult>> multiSimilar(const vector<path>& paths, vector<int> querys, const string &algorithm, int limit) {
    subResult empty;
    int cal = 0;
    empty.second = MaxSimilar;
    map<int, vector<int>> pointGrid;
    map<int, vector<subResult>> record;
    map<int, vector<int>> pathId;
    map<int, map<int, subResult>> results;
    map<int, double> lowerBound;
    map<int, vector<point>> points;
    map<int, path> queryPaths;
    string targetFile = filepath;
    {
        targetFile.append(to_string(minLen));
        targetFile.append("_");
        targetFile.append(to_string(maxLen));
        targetFile.append("_");
        targetFile.append(matricsType);
        targetFile.append("_result.txt");
    }
    ofstream ofs(targetFile, ios::app);
    for (auto i = querys.begin(); i < querys.end(); ++i) {
        if (paths[*i].size() < minLen) {
            i = querys.erase(i);
            i --;
        } else if (paths[*i].size() > maxLen) {
            path tmp(paths[*i].begin(), paths[*i].begin() + maxLen);
            queryPaths[*i] = tmp;
        } else {
            queryPaths[*i] = paths[*i];
        }
    }

    for (const auto &item : querys) {
        auto queryPath = queryPaths[item];
        for (int i = 0; i < keyNum; ++i) {
            points[item].push_back(queryPath[(i + 1) * queryPath.size() / (keyNum + 1)]);
        }
        lowerBound[item] = MaxSimilar;
    }
    if (gatherType == "gridbase") {
        pointGrid = initGrid(points);
    }
    for (int i = 0; i < paths.size(); ++i) {
        map<int, bool> multiLowBounds;
        if (gatherType == "gridbase") {
            multiLowBounds = multiLowBoundEstimateGridBase(pointGrid, paths[i], querys, 2);
        } else {
            multiLowBounds = multiLowBoundEstimate(points, paths[i], paths, lowerBound, 2);
        }
        for (const auto &query : querys) {
            auto queryPath = queryPaths[query];
            if (i != query && paths[i].size() > queryPath.size() && multiLowBounds[query]) {
                auto res = execute(algorithm, queryPath, paths[i]);
                cal ++;
                bool flag = false;
                for (int j = 0; j < record[query].size(); ++j) {
                    if (record[query][j].second > res.second) {
                        record[query].insert(record[query].begin() + j, res);
                        pathId[query].insert(pathId[query].begin() + j, i);
                        flag = true;
                        if (generateResult) {
                            ofs << query << "," << i << "," << res.first.first << "," << res.first.second << "," << res.second << endl;
                        }
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
    ofs.close();
    for (const auto &query : querys) {
        if (pathId[query].empty()) continue;
        for (int i = 0; i < min(limit, (int)pathId[query].size()); ++i) {
            results[query][pathId[query][i]] = record[query][i];
        }
    }
    cout << cal << endl;
    return results;
}
