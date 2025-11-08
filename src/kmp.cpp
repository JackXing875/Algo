#include <string>
#include <vector>
#include <iostream>

std::vector<int> prefix(std::string str) {
    std::vector<int> lps(str.size(), 0);

    for (int i = 1; i < str.size(); i++) {
        int j = lps[i-1];

        while (j > 0 && str[i] != str[j]) 
            j = lps[j-1];
        
        if (str[i] == str[j]) j++;

        lps[i] = j;
    }

    return lps;
}

std::vector<int> kmp(std::string text, std::string pattern) {
    if (pattern.empty()) return {};

    std::vector<int> pos;
    std::vector<int> lps = prefix(pattern);
    int j = 0;

    for (int i = 0; i < text.size(); i++) {
        while (j > 0 && text[i] != pattern[j]) 
            j = lps[j-1];

        if (text[i] == pattern[j]) j++;

        if (j == pattern.size()) {
            pos.push_back(i-j+1);
            j = lps[j-1];
        }
    }

    return pos;
}