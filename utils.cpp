//
// Created by 86173 on 2022/1/27.
//


#include <iomanip>
#include "utils.h"


path str2path(const string &s) {
    vector<pair<double, double>> path;
    for (char i : s) {
        path.emplace_back(i, i);
    }
    return path;
}

void file2paths(const string &filename, const string& target, int bound = -1) {
    ifstream ifs(filename);
    ofstream ofs(target);
    string s;
    map<string, vector<pair<int, pair<double, double>>>> tmp_data;
    string tmp;
    int driverCount = 0, trajectoryCount = 0;
    while (!ifs.eof()) {
        if (bound > 0 && trajectoryCount >= bound) break;
        getline(ifs, s);
        auto strs = split(s, ",");
        if(tmp != strs[0]) {
            for (auto id: tmp_data) {
                sort(id.second.begin(), id.second.end());
                ofs << id.second.size() << endl;
                for (auto item: id.second) {
                    ofs << item.first << " " << setiosflags(ios::fixed) << setprecision(5) << item.second.first << " " << item.second.second << endl;
                }
                trajectoryCount ++;
            }
            driverCount ++;
            tmp = strs[0];
            tmp_data.clear();
            cout << tmp << endl;
        }
        double latitude, longitude;
        long t_index;
        string t = strs[2] + " " + strs[3] + " " + strs[4];
        istringstream istr1(t);
        istr1 >> t_index >> longitude >> latitude;
        pair<int, pair<double, double>> tt = {t_index, {latitude, longitude}};
        tmp_data[strs[1]].push_back(tt);
    }
    ifs.close();
    ofs.close();
    cout << trajectoryCount << endl;
}

vector<string> split(string str, string pattern) {
    string::size_type pos;
    vector<string> result;
    str += pattern;
    int size = str.size();

    for (int i = 0; i < size; i++) {
        pos = str.find(pattern, i);
        if (pos < size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

vector<path> readfile(const string &filename) {
    int point_num;
    vector<path> paths;
    ifstream ifs(filename);
    while (!ifs.eof()) {
        int time_index;
        double lat, lon;
        path p;
        ifs >> point_num;
        for (int i = 0; i < point_num; ++i) {
            ifs >> time_index >> lat >> lon;
            p.emplace_back(lat, lon);
        }
        paths.push_back(p);
    }
    return paths;
}

void paths2file(const string &filename, vector<path> paths) {
    ofstream ofs(filename);
    for (const auto &item : paths) {
        ofs << item.size() << endl;
        for (int i = 0; i < item.size(); ++i) {
            ofs << setiosflags(ios::fixed) << setprecision(5) << item[i].first << " " << item[i].second << endl;
        }
    }
    ofs.close();
}

void ids2file(const string &filename, const map<int, subResult>& paths, int queryID) {
    ofstream ofs(filename, ios::app);
    for (const auto &item : paths) {
        ofs << queryID << "," << item.first << "," << item.second.first.first << "," << item.second.first.second << "," << item.second.second << endl;
    }
    ofs.close();
}


void dataAnalize(const string& filename) {
    int count = 0;
    double avg_length = 0;
    double avg_lat = 0;
    double avg_lon = 0;
    double max_lat = -10000;
    double min_lat = 10000;
    double max_lon = -10000;
    double min_lon = 10000;

    int point_num;
    ifstream ifs(filename);
    while (!ifs.eof()) {
        int time_index;
        double lat, lon;
        ifs >> point_num;
        for (int i = 0; i < point_num; ++i) {
            ifs >> time_index >> lat >> lon;

        }
        avg_length = (count * avg_length + point_num) / (count + 1);
        avg_lat = (count * avg_lat + lat) / (count + 1);
        avg_lon = (count * avg_lon + lon) / (count + 1);
        count += 1;
        max_lat = max(max_lat, lat);
        min_lat = min(min_lat, lat);
        max_lon = max(max_lon, lon);
        min_lon = min(min_lon, lon);
    }
    cout << "avgLen:" << avg_length << endl;
    cout << "count:" << count << endl;
    cout << "max_lat:" << max_lat << endl;
    cout << "min_lat:" << min_lat << endl;
    cout << "avg_lat:" << avg_lat << endl;
    cout << "max_lon:" << max_lon << endl;
    cout << "min_lon:" << min_lon << endl;
    cout << "avg_lon:" << avg_lon << endl;
}

void dataFilter(const string &filename) {
    int point_num;
    int count = 0;
    ifstream ifs(filename);
    ofstream ofs(filename + "Tmp");

    while (!ifs.eof()) {
        int time_index;
        bool flag = true;
        double lat, lon;
        path p;
        ifs >> point_num;
        for (int i = 0; i < point_num; ++i) {
            ifs >> time_index >> lat >> lon;

            if (range[dataType].first[0] > lat || lat > range[dataType].first[1]){
                flag = false;
            }
            if (range[dataType].second[0] > lon || lon > range[dataType].second[1]){
                flag = false;
            }
            p.emplace_back(lat, lon);
        }
        if (!flag) continue;
        count ++;
        ofs << p.size() << endl;
        for (auto & i : p) {
            ofs << setiosflags(ios::fixed) << setprecision(5) << time_index << " " << i.first << " " << i.second << endl;
        }
    }
    cout << count << endl;
    ifs.close();
    ofs.close();
}