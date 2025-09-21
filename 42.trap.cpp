#include <vector>

class Solution 
{
public:
    int trap(std::vector<int>& height) 
    {
        if (height.empty()) return 0;

        std::vector<int> leftMax(height.size(), 0), rightMax(height.size(), 0);
        leftMax[0] = height[0], rightMax[height.size()-1] = height[height.size()-1];

        for (int i = 1; i < height.size(); i++)
            leftMax[i] = std::max(height[i], leftMax[i-1]);

        for (int i = height.size()-2; i >= 0; i--)
            rightMax[i] = std::max(height[i], rightMax[i+1]);

        int res = 0;

        for (int i = 0; i < height.size(); i++)
            res += std::min(leftMax[i], rightMax[i]) - height[i];

        return res;
    }
};