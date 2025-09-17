#include <iostream>
#include <vector>
#include <stdexcept>

template <typename datatype>
class ListNode
{
public:
    datatype val;
    ListNode<datatype>* next;

    ListNode(datatype x) : val(x), next(nullptr) {}; 
};

template <typename datatype>
class LinkedList
{
private:
    ListNode<datatype>* head;

public:
    LinkedList() : head(nullptr) {}

    void create(const std::vector<datatype>& array)
    {
        clear();
        if(array.empty()) 
        {
            head = nullptr;
            return ;
        }

        head = new ListNode<datatype>(array[0]);
        ListNode<datatype>* cur = head;

        for(size_t i = 1; i < array.size(); i++)
        {
            cur->next = new ListNode<datatype>(array[i]);
            cur = cur->next;
        }
    }

    bool isEmpty() const { return !head; }

    size_t getSize(ListNode<datatype>* head) const
    {
        ListNode<datatype>* cur = head;
        size_t num = 0;

        while(cur)
        {
            num++;
            cur = cur->next;
        }

        return num;
    }

    void traversal() const
    {
        ListNode<datatype>* cur = head;
        while(cur)
        {
            std::cout << cur->val << std::endl;
            cur = cur->next;
        }
    }

    void append(datatype value)
    {
        if(!head)
        {
            head = new ListNode<datatype>(value);
            return ;
        }

        ListNode<datatype>* cur = head;
        while(cur && cur->next) cur = cur->next;

        cur->next = new ListNode<datatype>(value);
    }

    datatype get(size_t index) 
    {
        if(!head) throw std::out_of_range("Cannot get value in an empty list");

        ListNode<datatype>* cur = head;
        size_t i = 0;

        while (cur && i < index) 
        {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        return cur->val;
    }

    void set(size_t index, datatype value)
    {
        if(!head) throw std::out_of_range("Empty list");

        ListNode<datatype>* cur = head;
        size_t i = 0;

        while (cur && i < index) 
        {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        cur->val = value;
    }

    void insert(size_t index, datatype value)
    {
        if(index == 0)
        {
            ListNode<datatype>* newnode = new ListNode<datatype>(value);
            newnode->next = head;
            head = newnode;
            return ;
        }

        ListNode<datatype>* cur = head;
        size_t i = 0;

        while (cur && i < index-1) 
        {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        ListNode<datatype>* temp = cur->next;

        cur->next = new ListNode<datatype>(value);
        cur->next->next = temp;
    }

    void remove(size_t index) 
    {
        if(!head)
            throw std::out_of_range("Cannot remove from an empty list");

        if(index == 0) 
        {
            ListNode<datatype>* newhead = head->next;
            delete head;
            head = newhead;
            return ;
        }

        ListNode<datatype>* cur = head;
        for(size_t i = 0;i < index - 1;i++) 
        {
            if(!cur->next)
                throw std::out_of_range("Index out of range");
            cur = cur->next;
        }

        if(!cur->next)
            throw std::out_of_range("Index out of range");

        ListNode<datatype>* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    }

    void clear()
    {
        ListNode<datatype>* cur = head;
        while(head)
        {
            ListNode<datatype>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    ~LinkedList()
    {
        clear();
    }
};