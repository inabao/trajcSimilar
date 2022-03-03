//
// Created by 86173 on 2022/1/27.
//

#include "similarTrajectory.h"

double minSubTrajectory(const path& path1, const path& path2) {
    double minDistance = 1000000;
    for (int i = 0; i < path2.size() - 1; ++i) {
        for (int j = i + 1; j < path2.size(); ++j) {
            minDistance = min(wedDistance(path1, path2, i, j), minDistance);
        }
    }
    return minDistance;
}


subResult efficientAlgorithmWED(path path1, path path2) {
    int lenPath1 = path1.size();
    int lenPath2 = path2.size();
    auto allCost = new double[path2.size()];
    auto allCostTmp = new double[path2.size()];
    auto starts = new int[path2.size()];
    auto startsTmp = new int[path2.size()];
    double empty[lenPath1];
    for (int i = 0; i < lenPath1; ++i) {
        if (i == 0) {
            empty[i] = distance(nullPoint, path1[i]);
        } else {
            empty[i] = empty[i - 1] + distance(nullPoint, path1[i]);
        }
    }
    for (int i = 0; i < lenPath1; ++i) {
        //        cout << "from:  ";
        for (int j = 0; j < lenPath2; ++j) {
            if (i == 0) {
                starts[j] = j;
                allCost[j] = distance(path1[0], path2[j]);
            } else{
                //                int x = 0;
                if (j == 0) {
                    allCost[0] = min(allCostTmp[0] + distance(nullPoint, path1[i]), empty[i-1] + distance(path1[i], path2[0]));
                    starts[0] = 0;
                    continue;
                }
                double c1 = allCostTmp[j] + distance(nullPoint, path1[i]);
                double c2 = allCostTmp[j - 1] + distance(path1[i], path2[j]);
                double c3 = allCost[j - 1] + distance(nullPoint, path2[j - 1]) - distance(path1[i], path2[j-1])
                        + (c2 - allCostTmp[j-1]);
                if (c1 >= c2) {
                    allCost[j] = c2;
                    starts[j] = startsTmp[j - 1];
                    //                    x = 0;
                } else {
                    allCost[j] = c1;
                    starts[j] = startsTmp[j];
                    //                    x = 1;
                }
                if (c3 < allCost[j]) {
                    starts[j] = starts[j-1];
                    allCost[j] = c3;
                    //                    x = -1;
                }
                //                cout << x << " ";

                /*
                 * 8945128451248657
                 * 9481659841637894616841131216574121965023657864513246364124863125628965130
                 */

            }
        }
        //        cout << endl;
        //        for (int j = 0; j < path2.size(); ++j) {
        //            cout << *(allCost + j) << " ";
        //        }
        //        cout << endl;
        swap(allCost,allCostTmp);
        swap(starts, startsTmp);
    }
    int start, end = 0;
    double res = allCostTmp[0];
    for (int j = 0; j < lenPath2; ++j) {
        if (res > allCostTmp[j]) {
            res = min(res, allCostTmp[j]);
            end = j;
        }
    }
    start = startsTmp[end];
    delete[] allCostTmp;
    delete[] allCost;
    delete[] starts;
    delete[] startsTmp;
    subResult r;
    r.first.first = start;
    r.first.second = end;
    r.second = res;
    return r;
}

subResult efficientAlgorithmDTW(path path1, path path2) {
    int lenPath1 = path1.size();
    int lenPath2 = path2.size();
    auto allCost = new double[path2.size()];
    auto allCostTmp = new double[path2.size()];
    auto starts = new int[path2.size()];
    auto startsTmp = new int[path2.size()];
    double empty[lenPath1];
    for (int i = 0; i < lenPath1; ++i) {
        if (i == 0) {
            empty[i] = pointDistance(path2[0], path1[i]);
        } else {
            empty[i] = empty[i - 1] + pointDistance(path2[0], path1[i]);
        }
    }
    for (int i = 0; i < lenPath1; ++i) {
        for (int j = 0; j < lenPath2; ++j) {
            if (i == 0) {
                starts[j] = j;
                allCost[j] = pointDistance(path1[0], path2[j]);
            } else {
                if (j == 0) {
                    starts[0] = 0;
                    allCost[0] = min(allCostTmp[0] + pointDistance(path2[0], path1[i]), empty[i-1] + pointDistance(path1[i], path2[0]));
                    continue;
                }
                if (allCostTmp[j] >= allCostTmp[j - 1]) {
                    starts[j] = startsTmp[j - 1];
                } else {
                    starts[j] = startsTmp[j];
                }
                if (allCostTmp[j] > allCost[j-1] && allCostTmp[j - 1] > allCost[j-1]) {
                    starts[j] = starts[j - 1];
                }
                allCost[j] = min(allCostTmp[j], min(allCostTmp[j - 1], allCost[j-1])) + pointDistance(path1[i], path2[j]);
            }
        }
        swap(allCost,allCostTmp);
        swap(starts, startsTmp);
    }
    int start;
    int end = 0;
    double res = allCostTmp[0];
    for (int j = 0; j < lenPath2; ++j) {
        if (res > allCostTmp[j]) {
            res = min(res, allCostTmp[j]);
            end = j;
        }
    }
    start = startsTmp[end];
    delete[] allCostTmp;
    delete[] allCost;
    delete[] starts;
    delete[] startsTmp;
    subResult r;
    r.first.first = start;
    r.first.second = end;
    r.second = res;
    return r;
}

subResult efficientAlgorithm(const path& path1, const path& path2) {
    if (matricsType == "dtw") {
        return efficientAlgorithmDTW(path1, path2);
    } else {
        return efficientAlgorithmWED(path1, path2);
    }
}