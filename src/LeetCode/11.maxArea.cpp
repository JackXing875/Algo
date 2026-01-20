#include <vector>

class Solution 
{
public:
    int maxArea(std::vector<int>& height) 
    {
        int left = 0, right = height.size()-1;
        int res = 0;

        while (left < right)
        {
            int cap = std::min(height[left], height[right]) * (right - left);
            res = std::max(res, cap);

            if (height[left] < height[right]) left++;
            else right--;
        }

        return res;
    }
};