#include <bits/stdc++.h>
using namespace std;

struct ware {
    int id;
    vector<int> pos;
};

bool cmp_big(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return false;

    for (int i = 0; i < a.size(); i++)
        if (a[i] <= b[i]) return false;

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<ware> w(n);

    for (int i = 0; i < n; i++) {
        w[i].id = i+1;
        for (int j = 0; j < m; j++) {
            int temp;
            cin >> temp;
            w[i].pos.push_back(temp);
        }
    }

    vector<int> res;

    for (int i = 0; i < n; i++) {
        ware cur = w[i];
        bool find = false;

        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            ware candidate = w[j];
            if (cmp_big(candidate.pos, cur.pos)) {
                find = true;
                res.push_back(candidate.id);
                break;
            }
        }

        if (!find) res.push_back(0);
    }

    for (int i = 0; i < n; i++)
        cout << res[i] << endl;
    return 0;  
}