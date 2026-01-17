#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> cnt(m + 1, 0);   
    vector<int> doc(m + 1, 0);   

    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;

        vector<bool> seen(m + 1, false);

        for (int j = 0; j < l; j++) {
            int x;
            cin >> x;

            cnt[x]++;             
            if (!seen[x]) {
                seen[x] = true;    
                doc[x]++;          
            }
        }
    }

    for (int i = 1; i <= m; i++) 
        cout << doc[i] << " " << cnt[i] << endl;
    

    return 0;
}
