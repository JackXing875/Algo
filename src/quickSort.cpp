#include <vector>
#include <iostream>

class Sort
{
public:
    template<typename T>
    void quickSort(std::vector<T> &arr,int left,int right)
    {
        if(left >= right) return;

        T i = left,j = right;
        T key = arr[i];

        while(i < j)
        {
            while(i < j && arr[j] >= key) j--;
            arr[i] = arr[j];
            while(i < j && arr[i] <= key) i++;
            arr[j] = arr[i];
            arr[i] = key;      
        }

        quickSort(arr,left,i-1);
        quickSort(arr,i+1,right);
    }
};

int main()
{
    Sort s;
    std::vector<int> arr = {5,2,9,1,5,6};
    s.quickSort(arr,0,arr.size()-1);
    for(int i = 0;i < arr.size();i++)
        std::cout << arr[i] << " ";
    return 0;
}