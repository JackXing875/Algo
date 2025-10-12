#include <iostream>

template <typename T>
class ListNode 
{
public:
    T data;
    ListNode<T> *next;

    ListNode(int x): data(x), next(nullptr) {};
};

template <typename T>
void deleteMin(ListNode<T> *head) 
{
    if (!head || !head->next) return; 

    ListNode<T> *minPrev = head;     
    ListNode<T> *curPrev = head;
    ListNode<T> *cur = head->next;

    while (cur) 
    {
        if (cur->data < minPrev->next->data)
            minPrev = curPrev;  
        curPrev = cur;
        cur = cur->next;
    }

    ListNode<T> *minNode = minPrev->next;
    minPrev->next = minNode->next;
    delete minNode;
}
