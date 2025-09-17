#include <iostream>
#include <stdexcept>

template <typename datatype>
class Array
{
private:
    datatype *elem;
    size_t _size;
    size_t _cap;

    void resize(size_t new_cap)
    {
        if (new_cap < 16) new_cap = 16;
        datatype* new_elem = new datatype[new_cap];

        for (size_t i = 0; i < _size; i++)
            new_elem[i] = elem[i];

        delete[] elem;
        elem = new_elem;
        _cap = new_cap;
    }

public:
    Array(size_t capacity = 16) : _size(0), _cap(capacity < 16 ? 16 : capacity) { elem = new datatype[_cap]; }

    ~Array() { delete[] elem; }

    size_t size() { return _size; }
    size_t cap() { return _cap; }
    bool is_empty() { return _size == 0; }

    datatype at(size_t index)
    {
        if (index >= _size) throw std::out_of_range("Index out of range");
        return elem[index];
    }

    void push_back(datatype item)
    {
        if (_size == _cap) resize(_cap * 2);
        elem[_size] = item;
        _size++;
    }

    void insert(size_t index, datatype item)
    {
        if (index > _size) throw std::out_of_range("Index out of range");
        if (_size == _cap) resize(_cap * 2);

        for (size_t i = _size; i > index; i--)
            elem[i] = elem[i - 1];

        elem[index] = item;
        _size++;
    }

    datatype pop_back()
    {
        if (_size == 0) throw std::underflow_error("Array is empty");

        datatype val = elem[_size - 1];
        _size--;

        if (_size > 0 && _size == _cap / 4) resize(_cap / 2);
        return val;
    }

    void remove_at(size_t index)
    {
        if (index >= _size) throw std::out_of_range("Index out of range");

        for (size_t i = index; i < _size - 1; i++)
            elem[i] = elem[i + 1];

        _size--;

        if (_size > 0 && _size == _cap / 4) resize(_cap / 2);
    }

    int find(datatype item)
    {
        for (size_t index = 0; index < _size; index++)
            if (elem[index] == item) return index;

        return -1;
    }
};