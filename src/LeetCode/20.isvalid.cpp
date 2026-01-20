#include <unordered_map>
#include <string>
#include <utility>
#include <stack>

class Solution {
public:
    bool isValid(std::string s) {
        int n = s.size();
        if (n % 2 == 1) {
            return false;
        }

        std::unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        std::stack<char> st;
        for (char ch: s) {
            if (pairs.count(ch)) {
                if (st.empty() || st.top() != pairs[ch]) {
                    return false;
                }
                st.pop();
            }
            else {
                st.push(ch);
            }
        }
        return st.empty();
    }
};