#include <iostream>
#include <cstdlib>
#include <cassert>

typedef int datatype;

struct Node 
{
    datatype data;
    Node *next;

    Node() : data(0), next(nullptr) {}
    Node(datatype x) : data(x), next(nullptr) {} 
};

class LinkedList 
{
private:
    Node *head;

    Node* NodeCreate(datatype x) 
    {
        Node *newnode = new Node();
        if (!newnode) 
        {
            std::cerr << "Memory allocation failed!" << std::endl;
            exit(-1);
        }
        newnode->data = x;
        newnode->next = nullptr;
        return newnode;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() { ListClear(); } 

    Node* asLinkedList(int *arr, int n)
    {
        if (!arr || n <= 0) return nullptr;

        Node* head = new Node(arr[0]);
        Node* cur = head;

        for (int i = 1; i < n; i++) {
            cur->next = new Node(arr[i]);
            cur = cur->next;
        }

        return head;
    }

    
    void ListPrint() 
    {
        Node *ptr_temp = head;
        while (ptr_temp) 
        {
            std::cout << ptr_temp->data << std::endl;
            ptr_temp = ptr_temp->next;
        }
        std::cout << "NULL" << std::endl;
    }

    void ListPushback(datatype val) 
    {
        Node *newnode = NodeCreate(val);
        if (!head) head = newnode;
        else 
        {
            Node *ptr_temp = head;
            while (ptr_temp->next)
                ptr_temp = ptr_temp->next;
            ptr_temp->next = newnode;
        }
    }

    void ListPushfront(datatype val) 
    {
        Node *newnode = NodeCreate(val);
        newnode->next = head;
        head = newnode;
    }

    void ListPopback() 
    {
        assert(head); 
        if (!head->next) 
        {
            delete head;
            head = nullptr;
        }
        else 
        {
            Node *ptr_temp = head;
            while (ptr_temp->next && ptr_temp->next->next)
                ptr_temp = ptr_temp->next;
            Node *last = ptr_temp->next;
            ptr_temp->next = nullptr;
            delete last;
        }
    }

    void ListPopfront() 
    {
        assert(head);
        Node *second_node = head->next;
        delete head;
        head = second_node;
    }

    void ListInsert(Node *pos, datatype x) 
    {
        assert(pos); 
        Node *newnode = NodeCreate(x);
        Node *next = pos->next;
        pos->next = newnode;
        newnode->next = next;
    }

    void ListErase(Node *pos) 
    {
        assert(pos);
        if (head == pos) 
        {
            head = head->next;
            delete pos;
        } 
        else 
        {
            Node *ptr_temp = head;
            while (ptr_temp->next && ptr_temp->next != pos)
                ptr_temp = ptr_temp->next;
            if (ptr_temp->next == pos) 
            {
                ptr_temp->next = pos->next;
                delete pos;
            }
        }
    }

    Node* ListFind(datatype x) 
    {
        Node *ptr_temp = head;
        while (ptr_temp) 
        {
            if (ptr_temp->data == x)
                return ptr_temp;
            ptr_temp = ptr_temp->next;
        }
        return nullptr;
    }

    void ListClear() 
    {
        while (head) 
        {
            Node *next = head->next;
            delete head;
            head = next;
        }
    }
};