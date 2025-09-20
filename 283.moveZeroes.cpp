#include <vector>

class Solution 
{
public:
    void moveZeroes(std::vector<int>& nums) 
    {
        int fast = 0, slow = 0;

        while (fast < nums.size())
        {
            if (nums[fast] != 0)
            {
                nums[slow] = nums[fast];
                slow++;
            }

            fast++;
        }

        for (int i = slow; i < nums.size(); i++)
            nums[i] = 0;
    }
};