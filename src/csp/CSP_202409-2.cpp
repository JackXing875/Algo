// 没招了
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MAX_CHAR = 128;

const int MAX_LOG = 62;

char dp[MAX_LOG][MAX_CHAR];

// 初始化
void init() {
    for (int i = 0; i < MAX_CHAR; i++) {
        dp[0][i] = (char)i;
    }
}

int main() {
    // 1. I/O 加速
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();

    string raw_str;
    getline(cin, raw_str);
    
    size_t first_hash = raw_str.find('#');
    size_t last_hash = raw_str.rfind('#');
    string s = "";
    if (first_hash != string::npos && last_hash != string::npos && last_hash > first_hash) {
        s = raw_str.substr(first_hash + 1, last_hash - first_hash - 1);
    }

    int n;
    if (!(cin >> n)) return 0;
    string line;
    getline(cin, line); 

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        while (line.empty()) { // 跳过空行
            if (!getline(cin, line)) break;
        }
        
        // 解析 #xy#
        size_t h = line.find('#');
        if (h != string::npos && h + 2 < line.length()) {
            unsigned char u = line[h + 1];
            unsigned char v = line[h + 2];
            dp[0][u] = v;
        }
    }

    for (int j = 1; j < MAX_LOG; j++) {
        for (int i = 0; i < MAX_CHAR; i++) {
            char mid = dp[j-1][i];
            dp[j][i] = dp[j-1][(unsigned char)mid];
        }
    }

    // 5. 处理查询
    int m;
    cin >> m;
    
    vector<long long> queries(m);
    for(int i = 0; i < m; i++) cin >> queries[i];

    char current_map[MAX_CHAR];

    for (int i = 0; i < m; i++) {
        long long k = queries[i];

        for (int c = 0; c < MAX_CHAR; c++) {
            int current_char = c;
            long long temp_k = k;
            
            for (int j = 0; j < MAX_LOG; j++) {
                if ((temp_k >> j) & 1) {
                    current_char = dp[j][current_char];
                }
            }
            current_map[c] = (char)current_char;
        }

        cout << "#";
        for (char c : s) {
            cout << current_map[(unsigned char)c];
        }
        cout << "#" << endl;
    }

    return 0;
}