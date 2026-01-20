#include <iostream>
#include <stdexcept>

template <typename datatype>
class ArrayList
{
private:
    datatype* array;
    size_t size;
    size_t cap;

    const static size_t INIT_CAP = 1;

public:
    ArrayList() : size(0), cap(INIT_CAP) { this->array = new datatype[cap]; }

    ArrayList(size_t init_cap) : size(0), cap(init_cap) { this->array = new datatype[init_cap]; }

    ArrayList(size_t init_size, const datatype& default_value) : size(init_size), cap(std::max(init_size, INIT_CAP)) 
    {
    array = new datatype[cap];
    for (size_t i = 0; i < size; i++)
        array[i] = default_value;
    }


    ArrayList(const ArrayList& other) : size(other.size), cap(other.cap)
    {
        array = new datatype[cap];
        std::copy(other.array, other.array + size, array);
    }

    ArrayList& operator=(const ArrayList& other)
    {
        if (this == &other) return *this;

        datatype* new_array = new datatype[other.cap];
        std::copy(other.array, other.array + other.size, new_array);

        delete[] array;

        array = new_array;
        size = other.size;
        cap = other.cap;

        return *this;
    }

    size_t getSize() const { return size; }

    size_t capacity() const { return cap; }

    bool isEmpty() const { return size == 0; }

    void resize(size_t new_cap)
    {
        if (new_cap < size)
            throw std::invalid_argument("New capacity can't be less than current size.");
        
        datatype* temp = new datatype[new_cap];

        for(int i = 0; i < size; i++)
            temp[i] = array[i];

        delete[] array;

        array = temp;
        cap = new_cap;
    }

    void shrink_to_fit() { resize(std::max(size, INIT_CAP)); }

    void append(datatype val)
    {
        if(size == cap) resize(2*cap);

        array[size++] = val;
    }

    void add(size_t index, datatype val)
    {
        if(index > size) 
            throw std::out_of_range("Index out of bounds");

        if(size == cap) resize(2*cap);

        if(index == size)
        {
            append(val);
            return;
        }

        for(int i = size; i > index;i--)
            array[i] = array[i-1];

        array[index] = val;
        size++;
    }

    void pop()
    {
        if(isEmpty()) 
            throw std::out_of_range("No Such Element Exception");

        if (size > 0 && size <= cap / 4 && cap > INIT_CAP)
            resize(std::max(cap / 2, INIT_CAP));

        array[size-1] = datatype();
        size--;
    }

    void remove(size_t index)
    {
        if(index >= size)
            throw std::out_of_range("Index out of bounds");

        if (size > 0 && size <= cap / 4 && cap > INIT_CAP)
            resize(std::max(cap / 2, INIT_CAP));

        for (size_t i = index; i < size - 1; ++i)
            array[i] = array[i + 1];

        array[size-1] = datatype();
        size--;
    }

    datatype get(size_t index) const
    {
        if(index >= size)
            throw std::out_of_range("Index out of bounds");
        
        return array[index];
    }

    void set(size_t index, datatype element)
    {
        if(index >= size) 
            throw std::out_of_range("Index out of bounds");
        
        array[index] = element;
    }

    void clear(bool shrink = false)
    {
        for(size_t i = 0; i < size; i++)
            array[i] = datatype();

        size = 0;

        if(shrink && cap > INIT_CAP) resize(INIT_CAP);
    }

    datatype& operator[](size_t index)
    {
        if(index >= size)
            throw std::out_of_range("Index out of bounds");

        return array[index];
    }

    const datatype& operator[](size_t index) const
    {
        if(index >= size)
            throw std::out_of_range("Index out of bounds");

        return array[index];
    }

    datatype* begin() { return array; }
    datatype* end() { return array + size;}

    const datatype* begin() const { return array; }
    const datatype* end() const {return array + size; }

    ~ArrayList() { delete[] array; }
};