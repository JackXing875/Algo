#include <vector>
#include <string>
#include <iostream>

std::vector<int> prefix(std::string str) {
    std::vector<int> next(str.size(), 0);
    std::vector<int> nextVal(str.size(), 0);

    for (int i = 1; i < str.size(); i++) {
        int j = next[i-1];

        while (j > 0 && str[i] != str[j])
            j = next[j-1];

        if (str[i] == str[j])
            j++;
        
        next[i] = j;
    }

    nextVal = next;
    
    for (int i = 0; i < str.size(); i++) 
        if (str[i] == str[next[i]])
            nextVal[i] = next[nextVal[i]];
    
    return nextVal;
}

std::vector<int> kmp(std::string text, std::string pattern) {
    if (pattern.empty()) return {};
    std::vector<int> nextVal = prefix(pattern);
    std::vector<int> res;
    int j = 0;

    for (int i = 0; i < text.size(); i++) {
        while (j > 0 && text[i] != pattern[j])
            j = nextVal[j-1];

        if (text[i] == pattern[j]) j++;

        if (j == pattern.size()) {
            res.push_back(i-j+1);
            j = nextVal[j-1];
        }
    }

    return res;
}

int main(int argc, char *argv[]) {
    std::string text = "abacabbacab", pattern = "cab";
    std::vector<int> res = kmp(text, pattern);

    for (auto i: res) 
        std::cout << i << std::endl;
    std::cout << std::endl;

    return 0;
}