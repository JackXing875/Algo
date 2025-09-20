#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution 
{
public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) 
    {
        std::unordered_map<std::string, std::vector<std::string>> hashmap;

        for (auto str: strs)
        {
            std::string temp = str;
            sort(str.begin(), str.end());
            hashmap[str].push_back(temp);
        }

        std::vector<std::vector<std::string>> res;

        for (auto pairs: hashmap)
            res.push_back(pairs.second);

        return res;
    }
};