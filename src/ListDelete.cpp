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
void deleteNode(ListNode<T> *&head)
{
    if (!head) return;

    if (!head->next)
    {
        delete head;
        head = nullptr;
        return;
    }

    ListNode<T> *minPrev = nullptr;
    ListNode<T> *minNode = head;

    ListNode<T> *prev = nullptr;
    ListNode<T> *cur = head;

    while (cur)
    {
        if (cur->data < minNode->data)
        {
            minNode = cur;
            minPrev = prev;
        }
        prev = cur;
        cur = cur->next;
    }

    if (minPrev)
        minPrev->next = minNode->next;
    else
        head = minNode->next;

    delete minNode;
}

int main(int argc, char *argv[])
{
    ListNode<int>* head = new ListNode<int>(4);
    head->next = new ListNode<int>(2);
    head->next->next = new ListNode<int>(5);
    head->next->next->next = new ListNode<int>(3);

    deleteNode(head);

    for (ListNode<int>* p = head; p; p = p->next)
        std::cout << p->data << " ";
    
    std::cout << std::endl;

    return 0;
}