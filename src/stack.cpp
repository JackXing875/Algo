#include <vector>
#include <stdexcept>

template<typename datatype>
class stack
{
private:
    std::vector<datatype> array;

public:
    bool isEmpty() const { return array.size() == 0; }
    
    void push(datatype val) { array.push_back(val); }

    datatype pop()
    {
        if(isEmpty()) 
            throw std::out_of_range("Stack is empty");
        
        datatype topElement = array.back();
        array.pop_back();
        return topElement;
    }

    datatype top() 
    {
        if(isEmpty()) 
            throw std::out_of_range("Stack is empty");

        return array.back();
    }

    size_t size() const { return array.size(); }

    void clear() { array.clear(); }
};