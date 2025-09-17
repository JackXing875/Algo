#include <vector>
#include <algorithm>
#include <iostream>

class Sort
{
public:
    template <typename T>
    void selectionSort(std::vector<T> &arr)
    {
        int n = arr.size();
        for(int i = 0;i < n-1;i++)
        {
            int minIndex = i;
            for(int j = i;j < n;j++)
                if(arr[j] < arr[minIndex])
                    minIndex = j;
            if(minIndex != i)
                std::swap(arr[i],arr[minIndex]);
        }
    }
};

int main()
{
    Sort s;
    std::vector<int> arr = {5,2,9,1,5,6};
    s.selectionSort(arr);
    for(int i = 0;i < arr.size();i++)
        std::cout << arr[i] << " ";
    return 0;
}