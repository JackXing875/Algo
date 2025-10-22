#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

namespace ds {

template <typename T>
class Node {
public:
    T val;
    Node<T>* next;

    Node(T x) : val(x), next(nullptr) {}; 
};

template <typename T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void create(const std::vector<T>& array) {
        clear();
        if(array.empty()) {
            head = nullptr;
            return ;
        }

        head = new Node<T>(array[0]);
        Node<T>* cur = head;

        for(size_t i = 1; i < array.size(); i++) {
            cur->next = new Node<T>(array[i]);
            cur = cur->next;
        }
    }

    bool isEmpty() const { return !head; }

    size_t getSize() const {
        Node<T>* cur = head;
        size_t num = 0;

        while(cur) {
            num++;
            cur = cur->next;
        }

        return num;
    }

    void traversal() const {
        Node<T>* cur = head;
        while(cur) {
            std::cout << cur->val << std::endl;
            cur = cur->next;
        }
    }

    void append(T value) {
        if(!head) {
            head = new Node<T>(value);
            return ;
        }

        Node<T>* cur = head;
        while(cur->next) cur = cur->next;

        cur->next = new Node<T>(value);
    }

    T get(size_t index) {
        if(!head) throw std::out_of_range("Cannot get value in an empty list");

        Node<T>* cur = head;
        size_t i = 0;

        while (cur && i < index) {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        return cur->val;
    }

    void set(size_t index, T value) {
        if(!head) throw std::out_of_range("Empty list");

        Node<T>* cur = head;
        size_t i = 0;

        while (cur && i < index) {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        cur->val = value;
    }

    void insert(size_t index, T value) {
        if(index == 0) {
            Node<T>* newnode = new Node<T>(value);
            newnode->next = head;
            head = newnode;
            return ;
        }

        Node<T>* cur = head;
        size_t i = 0;

        while (cur && i < index-1) {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        Node<T>* temp = cur->next;

        cur->next = new Node<T>(value);
        cur->next->next = temp;
    }

    void remove(size_t index) {
        if(!head)
            throw std::out_of_range("Cannot remove from an empty list");

        if(index == 0) {
            Node<T>* newhead = head->next;
            delete head;
            head = newhead;
            return ;
        }

        Node<T>* cur = head;
        for(size_t i = 0;i < index - 1;i++) {
            if(!cur->next)
                throw std::out_of_range("Index out of range");
            cur = cur->next;
        }

        if(!cur->next)
            throw std::out_of_range("Index out of range");

        Node<T>* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    }

    void clear() {
        while(head) {
            Node<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    Node<T>* getHead() const { return head; }

    ~LinkedList() {
        clear();
    }
};

template <typename T>
class stack {
private:
    Node<T> *top; 

public:
    stack() : top(nullptr) {}

    // 压栈
    void push(T value) {
        Node<T> *newnode = new Node<T>(value); 
        newnode->next = top;              
        top = newnode;                   
    }

    // 弹栈
    void pop() {
        if (isEmpty()) {
            std::cout << "栈是空的，无法弹出" << std::endl; 
            return ;
        }

        Node<T> *temp = top;
        top = top->next; 
        delete temp;            
    }

    // 取栈顶元素
    T getTop() const {
        if (isEmpty()) {
            throw std::out_of_range("查看失败，栈已空");
        }
        return top->val; // 返回栈顶元素
    }

    bool isEmpty() const {
        return top == nullptr; 
    }
};

}