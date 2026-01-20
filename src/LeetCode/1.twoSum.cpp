#include <vector>
#include <unordered_map>

class Solution 
{
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        std::unordered_map<int, int> hashmap;

        for (int i = 0; i < nums.size(); i++)
        {
            int com = target - nums[i];
            
            if (hashmap.find(com) != hashmap.end())
                return {hashmap[com], i};

            hashmap[nums[i]] = i; 
        }
        
        return {};
    }
};