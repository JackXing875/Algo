#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;

    while (q--) {
        long long n, k;
        cin >> n >> k;

        long long res = 1;
        long long tmp = n;

        for (long long i = 2; i * i <= tmp; i++) {
            if (tmp % i != 0) continue;

            int cnt = 0;
            while (tmp % i == 0) {
                tmp /= i;
                cnt++;
            }

            if (cnt >= k) {
                for (int j = 0; j < cnt; j++)
                    res *= i;
            }
        }

        if (tmp > 1) {
            if (k <= 1) res *= tmp;
        }

        cout << res << '\n';
    }

    return 0;
}
