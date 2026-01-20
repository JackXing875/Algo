#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    unordered_map<string, int> cnt;
    vector<int> num;
    
    for (int k = 0; k < n; k++) { 
        string cur = "";
        string row;               

        for (int i = 0; i < 8; i++) {
            cin >> row;            
            cur += row;  
        }

        cnt[cur]++;
        num.push_back(cnt[cur]);

    }

    for (auto i: num)
        cout << i << endl;
    return 0;
}