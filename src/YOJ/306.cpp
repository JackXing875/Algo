#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int num;
    cin >> num;
    vector<int> input(num);
    unordered_map<int, int> fre;
    int max;

    for (int i = 0; i < num; i++) {
        cin >> input[i];
        fre[input[i]] = 0;
    }

    for (int i = 0; i < num; i++) {
        fre[input[i]]++;
    }

    int max_num = INT_MAX;
    fre[max_num] = 1;
    int max_fre = 0;

    for (int i = 0; i < num; i++) {
        if (fre[input[i]] > fre[max_num]) {
            max_num = input[i];
            max_fre = fre[input[i]];
        } else if (fre[input[i]] > fre[max_num]) {
            if (input[i] > max_num) {
                max_num = input[i];
                max_fre = fre[input[i]];
            }
        }
    }

    if (max_num == INT_MAX) {
        cout << "NO" << endl;
        return 0;
    }

    cout << max_num << " " << max_fre << endl;
        
    return 0;
}