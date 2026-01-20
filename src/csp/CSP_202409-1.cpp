#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    while (n--) {
        string s;
        cin >> s;

        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        int cnt[256] = {0};

        for (unsigned char c : s) {
            cnt[c]++;

            if (isupper(c)) hasUpper = true;
            else if (islower(c)) hasLower = true;
            else if (isdigit(c)) hasDigit = true;
            else if (c == '#' || c == '*') hasSpecial = true;
        }

        bool hasLetter = hasUpper || hasLower;

        bool allLessEq2 = true;
        for (int i = 0; i < 256; i++) {
            if (cnt[i] > 2) {
                allLessEq2 = false;
                break;
            }
        }

        if (s.size() >= 6 && hasLetter && hasDigit && hasSpecial) {
            if (allLessEq2) cout << 2 << "\n";
            else cout << 1 << "\n";
        } else {
            cout << 0 << "\n";
        }
    }

    return 0;
}
