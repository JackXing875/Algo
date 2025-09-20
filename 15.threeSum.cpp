#include <vector>
#include <algorithm>
#include <unordered_set>

class Solution 
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> res;

        for (int i = 0; i < nums.size(); i++)
        {
            int left = i+1, right = nums.size()-1;
            int target = -nums[i];

            while (left < right)
            {
                int sum = nums[left] + nums[right];
                if (sum == target) res.push_back({nums[left], nums[right], target});
            }
        }
    }
};