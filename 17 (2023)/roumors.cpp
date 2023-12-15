#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main() {

    int n;
    cin >> n;

    vector<pair<bool, pair<string, string>>> paths(n);

    unordered_map<string, vector<int>> m;

    for (int i=0; i<n; i++) {

        string name1, path, name2;
        cin >> name1 >> path >> name2;

        if (path == "??") {
            paths[i] = make_pair(false, make_pair(name1, name2));

            if (m.find(name1) == m.end()) {
                m[name1] = vector<int>();
                m[name1].push_back(i);
            }
            else {
                m[name1].push_back(i);
            }
            if (m.find(name2) == m.end()) {
                m[name2] = vector<int>();
                m[name2].push_back(i);
            }
            else {
                m[name2].push_back(i);
            }
        }
        else {
            paths[i] = make_pair(true, make_pair(name1, name2));
        }
    }

    queue<string> q;

    for (int i=0; i<n; i++) {
        if (paths[i].first) {
            q.push(paths[i].second.second);
        }
    }

    while (!q.empty()) {
        string name = q.front();
        q.pop();

        vector<int> ids = m[name];

        for (int id : ids) {
            if (paths[id].first) {
                continue;
            }

            paths[id].first = true;

            if (paths[id].second.second == name) {
                paths[id].second.second = paths[id].second.first;
                paths[id].second.first = name;
            }

            q.push(paths[id].second.second);
        }
    }

    unordered_set<string> dst;

    for (int i=0; i<n; i++) {
        if (paths[i].first) {
            dst.insert(paths[i].second.second);
        }
    }

    unordered_set<string> src;

    for (int i=0; i<n; i++) {
        if (paths[i].first) {
            if (dst.find(paths[i].second.first) == dst.end()) {
                src.insert(paths[i].second.first);
            }
        }
    }


    for (int i=0; i<n; i++) {
        if (!paths[i].first) {
            src.insert(paths[i].second.first);
            src.insert(paths[i].second.second);
        }
    }

    vector<string> sorted(src.size());

    int count = 0;

    for (string source : src) {
        sorted[count++] = source;
    }

    sort(sorted.begin(), sorted.end());

    for (int i=0; i<sorted.size(); i++) {
        cout << sorted[i] << endl;
    }

    return 0;
}