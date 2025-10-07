#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 100;

class Node 
{
public:
    string key;
    int value;
    Node* next;
    Node(string k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable 
{
private:
    vector<Node*> table;

    int hashFunction(const string& key) 
    {
        int hashValue = 0;
        for (char c : key) 
            hashValue = (hashValue * 31 + c) % TABLE_SIZE; 
        
        return hashValue;
    }

public:
    HashTable() 
    {
        table.resize(TABLE_SIZE, nullptr);
    }

    void insert(const string& key, int value) 
    {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);

        if (table[index] == nullptr) 
            table[index] = newNode;
        else
        {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    int search(const string& key) 
    {
        int index = hashFunction(key);
        Node* current = table[index];
        
        while (current != nullptr) 
        {
            if (current->key == key)
                return current->value;
            
            current = current->next;
        }
        return -1; 
    }

    void remove(const string& key) 
    {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) 
        {
            if (current->key == key) 
            {
                if (prev == nullptr)
                    table[index] = current->next;
                else
                    prev->next = current->next;

                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void printTable()
    {
        for (int i = 0; i < TABLE_SIZE; ++i) 
        {
            if (table[i] != nullptr) 
            {
                Node* current = table[i];
                while (current != nullptr) 
                {
                    cout << "[" << current->key << ": " << current->value << "] ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }
};