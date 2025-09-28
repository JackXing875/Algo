#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cwchar>
#include <limits>
#include <unordered_map>

bool isChinesePunct(wchar_t ch)
{
    std::wstring chinesePuncts = L"，。！？；：《》【】（）“”‘’";

    return chinesePuncts.find(ch) != std::wstring::npos;
}

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

    void input()
    {
        this->clear();
        std::wstring text;
        std::wcout << L"请输入文本：" << std::endl;
        getline(std::wcin, text);

        std::wstring word;
        for (wchar_t ch : text)
        {
            if (iswpunct(ch) || iswspace(ch) || isChinesePunct(ch))
            {
                if (!word.empty())
                {
                    this->append(word);
                    word.clear();
                }
            }
            else word += ch;
        }
        if (!word.empty())
            this->append(word);
    }

    void print() const
    {
        ListNode<T> *temp = head;
        while (temp)
        {
            std::wcout << temp->val << " ";
            temp = temp->next;
        }      
        std::wcout << std::endl;
    }

    void create(const std::vector<T>& array)
    {
        clear();
        if (array.empty()) 
        {
            head = nullptr;
            return ;
        }

        head = new ListNode<T>(array[0]);
        ListNode<T>* cur = head;

        for (size_t i = 1; i < array.size(); i++)
        {
            cur->next = new ListNode<T>(array[i]);
            cur = cur->next;
        }
    }

    bool isEmpty() const { return !head; }

    size_t getLength() const
    {
        ListNode<T>* cur = head;
        size_t length = 0;

        while (cur)
        {
            length++;
            cur = cur->next;
        }

        return length;
    }

    void append(T value)
    {
        if (!head)
        {
            head = new ListNode<T>(value);
            return ;
        }

        ListNode<T>* cur = head;
        while (cur && cur->next) cur = cur->next;

        cur->next = new ListNode<T>(value);
    }

    T get(size_t index) 
    {
        if (!head) throw std::out_of_range("Cannot get value in an empty list");

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
        if (!head) throw std::out_of_range("Empty list");

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
        if (index == 0)
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

        ListNode<T> *temp = cur->next;

        cur->next = new ListNode<T>(value);
        cur->next->next = temp;
    }

    void remove(size_t index) 
    {
        if (!head)
            throw std::out_of_range("Cannot remove from an empty list");

        if (index == 0) 
        {
            ListNode<T>* newhead = head->next;
            delete head;
            head = newhead;
            return ;
        }

        ListNode<T>* cur = head;
        for (size_t i = 0;i < index - 1;i++) 
        {
            if (!cur->next)
                throw std::out_of_range("Index out of range");
            cur = cur->next;
        }

        if (!cur->next)
            throw std::out_of_range("Index out of range");

        ListNode<T>* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    }

    bool find(T value)
    {
        ListNode<T> *temp = head;

        while (temp)
        {
            if (temp->val == value)
                return true;
            temp = temp->next;
        }

        return false;
    }

    bool findSeq(const std::vector<T>& query)
    {
        if (query.empty()) return false;

        ListNode<T> *temp = head;

        while (temp)
        {
            if (temp->val == query[0])
            {
                ListNode<T> *cur = temp;
                bool flag = true;
                for (size_t i = 0; i < query.size(); i++)
                {
                    if (!cur || cur->val != query[i])
                    {
                        flag = false;
                        break;
                    }
                    cur = cur->next;
                }

                if (flag) return true;
            }
            temp = temp->next;
        }

        return false;
    }

    ListNode<T>* reverseList(ListNode<T> *head) 
    {
        ListNode<T> *prev = nullptr;
        ListNode<T> *cur = head;

        while (cur)
        {
            ListNode<T> *nextNode = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nextNode;
        }

        return prev;
    }

    bool isSymmetry()
    {
        ListNode<T> *slow = head, *fast = head;
        
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast) slow = slow->next;

        ListNode<T> *half = reverseList(slow);
        ListNode<T> *left = head, *right = half;

        while (right)
        {
            if(left->val != right->val)
                return false;
            left = left->next;
            right = right->next;
        }

        reverseList(half);

        return true;
    }

    void reverse() 
    {
        ListNode<T> *prev = nullptr;
        ListNode<T> *cur = head;

        while (cur)
        {
            ListNode<T> *nextNode = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nextNode;
        }

        head = prev;
    }

    std::unordered_map<T, int> build_diction()
    {
        ListNode<T>* cur = head;
        std::unordered_map<T, int> diction;

        while (cur != nullptr)
        {
            diction[cur->val]++;
            cur = cur->next;
        }

        return diction;
    }

    void clear()
    {
        ListNode<T>* cur = head;
        while (head)
        {
            ListNode<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    ~LinkedList() { clear(); }
};


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, ""); // 设置本地化支持
    LinkedList<std::wstring> list;
    list.input();
    int k = 0;

    std::wcout << L"1:打印当前字符串" << std::endl
              << L"2:插入单词" << std::endl
              << L"3:删除单词" << std::endl
              << L"4:倒置当前字符串" << std::endl
              << L"5:判断当前字符串是否是回文串" << std::endl
              << L"6:计算字符串词数" << std::endl
              << L"7:查找某个字符串是否存在" << std::endl
              << L"8:销毁当前字符串" << std::endl
              << L"9:生成词典" << std::endl
              << L"10:重新输入字符串" << std::endl
              << L"-1:退出操作" << std::endl;
    
    while (k != -1)
    {
        std::wcout << L"请选择你想进行的操作：" << std::endl;
        while (!(std::wcin >> k))
        {
            std::wcin.clear(); // 清除错误输入
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略缓冲区中的多余字符
            std::wcout << L"无效输入，请输入数字：" << std::endl;
        }
        std::wstring word;
        int index;
        std::unordered_map<std::wstring, int> diction;
        switch (k)
        {
        case 1:
            list.print();
            break;

        case 2:
        {
            std::wcout << L"请输入你要插入的单词" << std::endl;
            std::wcin >> word;
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::wcout << L"请输入你要插入的位置索引" << std::endl;
            std::wcin >> index;
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            try{
                list.insert(index, word);
            }              
            catch (const std::out_of_range& e)
            {
                std::wcout << L"索引超出范围，请重新输入！" << std::endl;
            }
            break;
        }

        case 3:
        {
            std::wcout << L"请输入你要删除的单词的位置索引" << std::endl;
            std::wcin >> index;
            list.remove(index);
            break;
        }

        case 4:
        {
            list.reverse();
            std::wcout << L"已完成反转" << std::endl;
            break;
        }

        case 5:
        {
            bool a = list.isSymmetry();
            std::wcout << (a ? L"是回文串" : L"不是回文串") << std::endl;
            break;
        }

        case 6:
        {
            int lenth = list.getLength();
            std::wcout << lenth << std::endl;
            break;
        }

        case 7:
        {
            std::wcout << L"请输入你要查找的词语：" << std::endl;
            std::wcin >> word;
            bool b = list.find(word);
            std::wcout << (b ? L"存在" : L"不存在") << std::endl;
            break;
        }

        case 8:
        {
            list.clear();
            std::wcout << L"销毁字符串请不要再对该字符串进行操作" << std::endl;
            break;
        }

        case 9:
        {
            std::unordered_map<std::wstring, int> diction = list.build_diction();
            for (auto it = diction.begin(); it != diction.end(); ++it)
                std::wcout << it->first << L": " << it->second << std::endl;
            break;
        }
        case 10:
        {
            list.input();
            break;
        }
        case -1:
            return 0;
        default:
            std::wcout << L"无效的选项，请重新选择。" << std::endl;
            break;
        }
        std::wcout << std::endl;
    }
}