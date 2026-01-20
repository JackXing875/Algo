#include<vector>
#include <stdexcept>

template<typename T>
class queue
{
private:
    std::vector<T> array;

public:
    bool isEmpty() const { return array.size() == 0; }

    size_t size() const { return array.size(); }

    void push(T val) { array.push_back(val); }

    void pop() 
    { 
        if(isEmpty())
            throw std::out_of_range("Queue is empty");
        array.erase(array.begin()); 
    }

    T& front() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return array.front();
    }

    const T& front() const {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return array.front();
    }
};