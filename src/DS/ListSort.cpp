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
class Sort
{
public:
    ListNode<T>* findMid(ListNode<T> *head)
    {
        if (!head) return nullptr;

        ListNode<T> *fast = head->next;
        ListNode<T> *slow = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode<T> *mid = slow->next;
        slow->next = nullptr;
        
        return mid;
    }

    ListNode<T>* sort(ListNode<T> *head)
    {
        if (!head || !head->next) return head;

        ListNode<T> *mid = findMid(head);
        ListNode<T> *left = head;
        ListNode<T> *right = mid;

        left = sort(left), right = sort(mid);
        
        return merge(left, right);
    }

    ListNode<T>* merge(ListNode<T>* h1, ListNode<T>* h2)
    {
        if (!h1) return h2;
        if (!h2) return h1;

        ListNode<T>* head = nullptr;
        if (h1->data < h2->data) {
            head = h1;
            h1 = h1->next;
        } else {
            head = h2;
            h2 = h2->next;
        }

        ListNode<T>* pre = head;

        while (h1 && h2) {
            if (h1->data < h2->data) {
                pre->next = h1;
                pre = h1;
                h1 = h1->next;
            } else {
                pre->next = h2;
                pre = h2;
                h2 = h2->next;
            }
        }

        pre->next = h1 ? h1 : h2;

        return head;
    }

};

int main(int argc, char *argv[]) {
    ListNode<int>* head = new ListNode<int>(4);
    head->next = new ListNode<int>(2);
    head->next->next = new ListNode<int>(1);
    head->next->next->next = new ListNode<int>(3);

    Sort<int> s;
    head = s.sort(head);

    for (ListNode<int>* p = head; p; p = p->next)
        std::cout << p->data << " ";
    std::cout << std::endl;
    return 0;
}
