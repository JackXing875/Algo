#include<vector>
#include <stdexcept>

template<typename datatype>
class queue
{
private:
    std::vector<datatype> array;

public:
    bool isEmpty() const { return array.size() == 0; }

    size_t size() const { return array.size(); }

    void push(datatype val) { array.push_back(val); }

    void pop() 
    { 
        if(isEmpty())
            throw std::out_of_range("Queue is empty");
        array.erase(array.begin()); 
    }

    datatype& front() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return array.front();
    }

    const datatype& front() const {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return array.front();
    }
};