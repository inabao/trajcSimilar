//
// Created by 86173 on 2022/1/27.
//

#include "exactS.h"

int pathend = 0;
int tmpend = 0;
int pathstart = 0;

double exactWedDistance(path path1, path path2, int start, int end) {
    auto distanceMatrix = new double[end - start + 1];
    auto distanceMatrixTmp = new double[end - start + 1];
    double minDistance = 1000000;
    distanceMatrixTmp[0] = 0;
    for (int j = start + 1; j < end + 1; ++j) {
        distanceMatrixTmp[j - start] = distanceMatrixTmp[j - start - 1] + distance(path2[j - 1], nullPoint);
    }
    for (int i = 1; i < path1.size() + 1; ++i) {
        for (int j = start; j < end + 1; ++j) {
            if (j == start) {
                distanceMatrix[0] = distanceMatrixTmp[0] + distance(path1[i-1], nullPoint);
                continue;
            }
            distanceMatrix[j - start] = min(distanceMatrixTmp[j - start - 1] + distance(path1[i-1], path2[j-1]),
                                               min(distanceMatrix[j - start - 1] + distance(nullPoint, path2[j-1]),
                                                   distanceMatrixTmp[j - start] + distance(nullPoint, path1[i-1])));
        }
        swap(distanceMatrixTmp, distanceMatrix);
    }
    for (int i = 1; i < end - start + 1; ++i) {
        if (distanceMatrixTmp[i] < AR) MR += 1;
        if (distanceMatrixTmp[i] < minDistance) {
            tmpend = i - 1;
            minDistance = distanceMatrixTmp[i];
        }
    }
    delete[] distanceMatrixTmp;
    delete[] distanceMatrix;
    return minDistance;
}



double exactLcssDistance(path path1, path path2, int start, int end) {
    auto distanceMatrix = new double[end - start + 1];
    auto distanceMatrixTmp = new double[end - start + 1];
    double minDistance = 1000000;
    distanceMatrixTmp[0] = 0;
    for (int j = start + 1; j < end + 1; ++j) {
        distanceMatrixTmp[j - start] = distanceMatrixTmp[j - start - 1] + distance(path2[j - 1], nullPoint);
    }
    for (int i = 1; i < path1.size() + 1; ++i) {
        for (int j = start; j < end + 1; ++j) {
            if (j == start) {
                distanceMatrix[0] = distanceMatrixTmp[0] + distance(path1[i-1], nullPoint);
                continue;
            }
            distanceMatrix[j - start] = min(distanceMatrix[j - start - 1] + distance(nullPoint, path2[j-1]),
                                                distanceMatrixTmp[j - start] + distance(nullPoint, path1[i-1]));
            if (abs(i - (j - start + 1)) < 3) {
                distanceMatrix[j - start] = min(distanceMatrix[j - start], distanceMatrixTmp[j - start - 1] + distance(path1[i-1], path2[j-1]));
            }
        }
        swap(distanceMatrixTmp, distanceMatrix);
    }
    for (int i = 1; i < end - start + 1; ++i) {
        if (distanceMatrixTmp[i] < minDistance) {
            tmpend = i - 1;
            minDistance = distanceMatrixTmp[i];
        }
    }
    delete[] distanceMatrixTmp;
    delete[] distanceMatrix;
    return minDistance;
}





double exactDTW(path path1, path path2, int start, int end) {
    auto distanceMatrix = new double[end - start + 1];
    auto distanceMatrixTmp = new double[end - start + 1];
    double minDistance = 1000000;
    distanceMatrixTmp[0] = 0;
    for (int j = start + 1; j < end + 1; ++j) {
        distanceMatrixTmp[j - start] = distanceMatrixTmp[j - start - 1] + pointDistance(path2[j - 1], path1[start]);
    }
    for (int i = 1; i < path1.size() + 1; ++i) {
        for (int j = start; j < end + 1; ++j) {
            if (j == start) {
                distanceMatrix[0] = distanceMatrixTmp[0] + pointDistance(path1[i-1], path2[start]);
                continue;
            }
            distanceMatrix[j - start] = min(distanceMatrixTmp[j - start - 1] + pointDistance(path1[i-1], path2[j-1]),
                                            min(distanceMatrix[j - start - 1] + pointDistance(path1[i-1], path2[j-1]),
                                                distanceMatrixTmp[j - start] + pointDistance(path1[i-1], path2[j-1])));
        }
        swap(distanceMatrixTmp, distanceMatrix);
    }
    for (int i = 1; i < end - start + 1; ++i) {
        if (distanceMatrixTmp[i] < AR) MR += 1;
        if (distanceMatrixTmp[i] < minDistance) {
            tmpend = i - 1;
            minDistance = distanceMatrixTmp[i];
        }
    }
    delete[] distanceMatrixTmp;
    delete[] distanceMatrix;
    return minDistance;
}

subResult exactS(const path& p1, const path& p2) {
    double minDistance = 1000000;
    for (int i = 0; i < p2.size() - 1; ++i) {
        double distance;
        if (matricsType == "dtw") {
            distance = exactDTW(p1, p2, i, p2.size());
        } else if (matricsType == "lcss") {
            distance = exactLcssDistance(p1, p2, i, p2.size());
        } else {
            distance = exactWedDistance(p1, p2, i, p2.size());
        }
        if (minDistance > distance) {
            pathstart = i;
            pathend = pathstart + tmpend;
            minDistance = distance;
        }
    }
    subResult r;
    r.first.first = pathstart;
    r.first.second = pathend;
    r.second = minDistance;
    return r;
}


void calScore(const path& p1, const path& p2, int start, int end) {
    MR = 1, RR = 0;
    for (int i = 0; i < p2.size() - 1; ++i) {
        if (matricsType == "dtw") {
            exactDTW(p1, p2, i, p2.size());
        } else if (matricsType == "lcss") {
            exactLcssDistance(p1, p2, i, p2.size());
        } else {
            exactWedDistance(p1, p2, i, p2.size());
        }
    }
    RR = MR / (p2.size() * (p2.size() + 1) / 2);
}

