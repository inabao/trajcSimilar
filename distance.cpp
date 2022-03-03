//
// Created by 86173 on 2022/1/27.
//

#include "distance.h"

double pointDistance(point p1, point p2) {
    return sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
//    return p1.first == p2.first ? 0:1;
}


double levenshteinDistance(point p1, point p2) {
    if (p1.first == p2.first && p1.second == p2.second) return 0;
    return 1;
}

double lcss(point p1, point p2) {
    if (p1.first == p2.first && p1.second == p2.second) return 0;
    if (p1.first == nullPoint.first) return 1;
    return 2;
}

double erp(point p1, point p2) {
    if (p1.first == nullPoint.first) {
        p1 = centerPoint;
    }
    if (p2.first == nullPoint.first) {
        p2 = centerPoint;
    }
    double distance = sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
    return distance;
}


double edr(point p1, point p2, double e) {
    double distance = sqrt((p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second));
    if (e < distance) return 1;
    return 0;
}

double distance(point p1, point p2) {
    if (matricsType == "levenshteinDistance") return levenshteinDistance(p1, p2);
    if (matricsType == "edr") return edr(p1, p2, 0.003);
    if (matricsType == "erp") return erp(p1, p2);
    if (matricsType == "lcss") return lcss(p1, p2);
    return 0;
}



double wedDistance(path path1, path path2, int start, int end) {
    auto distanceMatrix = new double[end - start + 1];
    auto distanceMatrixTmp = new double[end - start + 1];
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
        for (int j = 0; j < end + 1; ++j) {
            cout << distanceMatrix[j] << " ";
        }
        cout << endl;
        swap(distanceMatrixTmp, distanceMatrix);
    }
    double result = distanceMatrixTmp[end - start];
    delete[] distanceMatrix;
    delete[] distanceMatrixTmp;
    return result;
}

double dtwDistance(path path1, path path2, int start, int end) {
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
    double result = distanceMatrixTmp[end - start];
    delete[] distanceMatrix;
    delete[] distanceMatrixTmp;
    return result;
}

