#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cwchar>
#include <limits>

template <typename T>
class ListNode
{
public:
    T val;
    ListNode<T>* next;

    ListNode(T x) : val(x), next(nullptr) {}; 
};

template <typename T>
class LinkedList
{
private:
    ListNode<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void print(LinkedList<T> list)
    {
        ListNode<T> temp = head;
        while (temp)
            std::cout << temp->val << std::endl;
    }

    void create(const std::vector<T>& array)
    {
        clear();
        if(array.empty()) 
        {
            head = nullptr;
            return ;
        }

        head = new ListNode<T>(array[0]);
        ListNode<T>* cur = head;

        for(size_t i = 1; i < array.size(); i++)
        {
            cur->next = new ListNode<T>(array[i]);
            cur = cur->next;
        }
    }

    bool isEmpty() const { return !head; }

    size_t getSize(ListNode<T>* head) const
    {
        ListNode<T>* cur = head;
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
        ListNode<T>* cur = head;
        while(cur)
        {
            std::cout << cur->val << std::endl;
            cur = cur->next;
        }
    }

    void append(T value)
    {
        if(!head)
        {
            head = new ListNode<T>(value);
            return ;
        }

        ListNode<T>* cur = head;
        while(cur && cur->next) cur = cur->next;

        cur->next = new ListNode<T>(value);
    }

    T get(size_t index) 
    {
        if(!head) throw std::out_of_range("Cannot get value in an empty list");

        ListNode<T>* cur = head;
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

    void set(size_t index, T value)
    {
        if(!head) throw std::out_of_range("Empty list");

        ListNode<T>* cur = head;
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

    void insert(size_t index, T value)
    {
        if(index == 0)
        {
            ListNode<T>* newnode = new ListNode<T>(value);
            newnode->next = head;
            head = newnode;
            return ;
        }

        ListNode<T>* cur = head;
        size_t i = 0;

        while (cur && i < index-1) 
        {
            cur = cur->next;
            i++;
        }

        if (!cur)
            throw std::out_of_range("Index out of range");

        ListNode<T>* temp = cur->next;

        cur->next = new ListNode<T>(value);
        cur->next->next = temp;
    }

    void remove(size_t index) 
    {
        if(!head)
            throw std::out_of_range("Cannot remove from an empty list");

        if(index == 0) 
        {
            ListNode<T>* newhead = head->next;
            delete head;
            head = newhead;
            return ;
        }

        ListNode<T>* cur = head;
        for(size_t i = 0;i < index - 1;i++) 
        {
            if(!cur->next)
                throw std::out_of_range("Index out of range");
            cur = cur->next;
        }

        if(!cur->next)
            throw std::out_of_range("Index out of range");

        ListNode<T>* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    }

    void clear()
    {
        ListNode<T>* cur = head;
        while(head)
        {
            ListNode<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    ~LinkedList()
    {
        clear();
    }
};

bool isChinesePunct(wchar_t ch)
{
    std::wstring chinesePuncts = L"，。！？；：《》【】（）“”‘’";

    return chinesePuncts.find(ch) != std::wstring::npos;
}

LinkedList<std::wstring> input()
{
    LinkedList<std::wstring> list;
    std::wstring text;
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::wcout << L"请输入文本：" << std::endl;
    std::getline(std::wcin, text);

    std::wstring word;
    for (wchar_t ch : text)
    {
        if (iswpunct(ch) || iswspace(ch) || isChinesePunct(ch))
            if (!word.empty())
            {
                list.append(word);
                word.clear();
            }
        else word += ch;

        if (!word.empty())
            list.append(word);
    }
}

void split(const std::string& text, ListNode<std::string> *head)
{
    std::string temp;
    ListNode<std::string> *tail;


}


ListNode<std::string>* load(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return nullptr;
    }
    std::string line, text;
    while (getline(fin, line)) {
        text += line + " ";
    }
    fin.close();

    ListNode<std::string>* head = nullptr;
    split(text, head);
    return head;
}
