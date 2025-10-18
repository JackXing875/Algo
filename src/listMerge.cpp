#include <iostream>

template <typename T>
class ListNode 
{
public:
    T val;
    ListNode<T> *next;

    ListNode(int x): data(x), next(nullptr) {};
};

template <typename T>
ListNode<T>* listMerge(ListNode<T> *h1, ListNode<T> *h2)
{
    if (!h1 || !h2) return nullptr;
    ListNode<T> *head = new ListNode<T>(0);
    ListNode<T> *cur = head;

    while (h1 && h2)
    {
        if (h1->val == h2->val)
        {
            cur->next = new ListNode<T>(h1->val);
            cur = cur->next;
            h1 = h1->next;
            h2 = h2->next;
        }

        else if (h1->val < h2->val)
            h1 = h1->next;

        else h2 = h2->next;
    }

    return head->next;

}