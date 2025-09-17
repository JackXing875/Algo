#include <vector>
#include <algorithm>
#include <iostream>

class Sort
{
public:
    template <typename T>
    void merge(std::vector<T> &arr,int left,int mid,int right)
    {
        std::vector<T> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        int leftSize = leftArr.size();
        int rightSize = rightArr.size();

        int i = 0,j = 0,k = left;

        while(i < leftSize && j < rightSize)
        {
            if(leftArr[i] <= rightArr[j])
                arr[k++] = leftArr[i++];
            else arr[k++] = rightArr[j++];
        }

        while(i < leftSize)
            arr[k++] = leftArr[i++];
        
        while(j < rightSize)
            arr[k++] = rightArr[j++];
    }

    template <typename T>
    void mergeSort(std::vector<T> &arr,int left,int right)
    {
        if(left == right) return;

        int mid = left + (right - left) / 2;

        mergeSort(arr,left,mid);
        mergeSort(arr,mid+1,right);
        merge(arr,left,mid,right);
    }
};

int main()
{
    Sort s;
    std::vector<int> arr = {5,2,9,1,5,6};
    s.mergeSort(arr,0,arr.size()-1);
    for(int i = 0;i < arr.size();i++)
        std::cout << arr[i] << " ";
    return 0;
}