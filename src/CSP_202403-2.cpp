#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> one;
    vector<string> two;

    unordered_set<string> bing;
    unordered_map<string, bool> flag1, flag2; 

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        one.push_back(s);
        bing.insert(s);
    }

    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return tolower(c); });
        two.push_back(s);
        bing.insert(s);
    }

    int num = 0;

    for (auto s: bing) {
        if ((find(one.begin(), one.end(), s) != one.end()) && (find(two.begin(), two.end(), s) != two.end()))
            num++;
    }

    cout << num << "\n" << bing.size() << endl;
    return 0;
}