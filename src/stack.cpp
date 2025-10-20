#include <vector>
#include <stdexcept>

template<typename T>
class stack
{
private:
    std::vector<T> array;

public:
    bool isEmpty() const { return array.size() == 0; }
    
    void push(T val) { array.push_back(val); }

    T pop()
    {
        if(isEmpty()) 
            throw std::out_of_range("Stack is empty");
        
        T topElement = array.back();
        array.pop_back();
        return topElement;
    }

    T top() 
    {
        if(isEmpty()) 
            throw std::out_of_range("Stack is empty");

        return array.back();
    }

    size_t size() const { return array.size(); }

    void clear() { array.clear(); }
};