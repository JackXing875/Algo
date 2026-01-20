#include <vector>
#include <unordered_set>

class Solution
{
public:
    int longestConsecutive(std::vector<int>& nums) 
    {
        int maxLen = 0;

        std::unordered_set<int> hashset(nums.begin(), nums.end());

        for (auto num: hashset)
        {
            if (hashset.find(num-1) == hashset.end())
            {
                int tempLen = 1;
                int cur = num;

                while (hashset.find(cur+1) != hashset.end())
                {
                    tempLen += 1;
                    cur++;
                }

                maxLen = std::max(tempLen, maxLen);
            }
            else continue;
        }

        return maxLen;
    }
};