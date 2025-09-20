#include <vector>
#include <algorithm>

class Solution 
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            int left = i+1, right = nums.size()-1;
            int target = -nums[i];

            while (left < right)
            {
                
            }
        }
    }
};