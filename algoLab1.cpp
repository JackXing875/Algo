// == 完整的改进部分（可直接替换你的文件） ==
#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <cwchar>
#include <limits>
#include <unordered_map>
#include <io.h>
#include <fcntl.h>
#include <codecvt>
#include <locale>
#include <windows.h>

// 判断是否是中文标点符号（分隔符）
bool isChinesePunct(wchar_t ch)
{
    std::wstring chinesePuncts = L"，。！？；：《》【】（）“”‘’";
    return chinesePuncts.find(ch) != std::wstring::npos;
}

// wstring (UTF-16) -> UTF-8 std::string
std::string wstringToUTF8(const std::wstring& wstr) {
    if (wstr.empty()) return {};
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(),
                                          nullptr, 0, nullptr, nullptr);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(),
                        &str[0], size_needed, nullptr, nullptr);
    return str;
}

// multibyte (given codepage) -> wstring
std::wstring multiByteToWString(const std::string& s, UINT codepage) {
    if (s.empty()) return {};
    int len = MultiByteToWideChar(codepage, 0, s.data(), (int)s.size(), nullptr, 0);
    if (len == 0) return {};
    std::wstring w(len, 0);
    MultiByteToWideChar(codepage, 0, s.data(), (int)s.size(), &w[0], len);
    return w;
}

// 简单检测是否为合法 UTF-8（用于没有 BOM 时判断）
bool isValidUTF8(const std::string& s) {
    const unsigned char *bytes = (const unsigned char*)s.c_str();
    size_t len = s.size();
    size_t i = 0;
    while (i < len) {
        unsigned char c = bytes[i];
        if ((c & 0x80) == 0) { // 0xxxxxxx
            i += 1;
        } else if ((c & 0xE0) == 0xC0) { // 110xxxxx 10xxxxxx
            if (i+1 >= len) return false;
            if ((bytes[i+1] & 0xC0) != 0x80) return false;
            i += 2;
        } else if ((c & 0xF0) == 0xE0) { // 1110xxxx 10xxxxxx 10xxxxxx
            if (i+2 >= len) return false;
            if ((bytes[i+1] & 0xC0) != 0x80 || (bytes[i+2] & 0xC0) != 0x80) return false;
            i += 3;
        } else if ((c & 0xF8) == 0xF0) { // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            if (i+3 >= len) return false;
            if ((bytes[i+1] & 0xC0) != 0x80 || (bytes[i+2] & 0xC0) != 0x80 || (bytes[i+3] & 0xC0) != 0x80) return false;
            i += 4;
        } else return false;
    }
    return true;
}

// 读取文件字节 -> 转为 std::wstring（自动检测 UTF-8 / UTF-16 LE / ANSI）
std::wstring readFileToWString(const std::wstring& wfilename) {
    std::string fname = wstringToUTF8(wfilename); // 用 UTF-8 名称打开文件（在 MinGW 下更可靠）
    std::ifstream fin(fname, std::ios::binary);
    if (!fin.is_open()) {
        return L""; // caller 处理错误
    }

    // 读取所有字节
    std::string content((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
    fin.close();

    if (content.empty()) return L"";

    // 检测 BOM 或编码
    // UTF-8 BOM: EF BB BF
    if (content.size() >= 3 &&
        (unsigned char)content[0] == 0xEF &&
        (unsigned char)content[1] == 0xBB &&
        (unsigned char)content[2] == 0xBF) {
        std::string noBom = content.substr(3);
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
        return conv.from_bytes(noBom);
    }

    // UTF-16 LE BOM: FF FE
    if (content.size() >= 2 &&
        (unsigned char)content[0] == 0xFF &&
        (unsigned char)content[1] == 0xFE) {
        // 使用 codecvt_utf16 (little endian)
        std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>, wchar_t> conv16;
        return conv16.from_bytes(content);
    }

    // 没有 BOM，先试 UTF-8 验证
    if (isValidUTF8(content)) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
        return conv.from_bytes(content);
    }

    // 兜底：按系统 ANSI（CP_ACP）解码（通常是 GBK 在中文 Windows）
    return multiByteToWString(content, CP_ACP);
}

//节点类
template <typename T>
class ListNode
{
public:
    T val;
    ListNode<T>* next;

    ListNode(T x) : val(x), next(nullptr) {}; 
};

//单链表类
template <typename T>
class LinkedList
{
private:
    ListNode<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void input()
    {
        clear();
        std::wstring text;   //wstring防止中文被拆碎
        std::wcout << L"请输入文本：" << std::endl;
        getline(std::wcin, text);

        std::wstring word;
        for (wchar_t ch : text)
        {
            if (iswpunct(ch) || iswspace(ch) || isChinesePunct(ch)) //如果是标点符号，就把词加入链表，并清空临时容器word
            {
                if (!word.empty())
                {
                    append(word);
                    word.clear();
                }
            }
            else word += ch; //如果不是标点，那就是当前词的一部分，加入当前词
        }
        if (!word.empty()) append(word);
    }

    void print() const //打印当前链表
    {
        ListNode<T> *temp = head;
        while (temp)
        {
            std::wcout << temp->val << " ";
            temp = temp->next;
        }      
        std::wcout << std::endl;
    }

    void create(const std::vector<T>& array) //由 std::vector 生成链表
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

    bool isEmpty() const { return !head; } //判断链表是否为空

    size_t getLength() const //获取链表长度
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

    void append(T value)  //在链表末尾增加节点
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

    T get(size_t index) //获取索引为 index 处的节点的值
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

    void set(size_t index, T value) //更改索引为 index 处的节点的值为 value
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

    void insert(size_t index, T value) //在索引为index处插入值为 value 的节点
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

    void remove(size_t index) //删除索引为 index 处的节点
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

    bool find(T value) //查找链表中是否包含值为 value 的节点
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

    bool findSeq(const std::vector<T>& query) //多个值匹配
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

    ListNode<T>* reverseList(ListNode<T> *head) //反转链表， 并返回新的头节点（仅作为工具函数来实现判断回文函数）
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

    bool isSymmetry() //判断链表是否为回文链表
    {
        ListNode<T> *slow = head, *fast = head;
        
        while (fast && fast->next) //找到中间的节点
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast) slow = slow->next;

        ListNode<T> *half = reverseList(slow); //反转链表的后半部分
        ListNode<T> *left = head, *right = half;

        while (right) //前后两部分一一比对，判断是否相同
        {
            if(left->val != right->val)
                return false;
            left = left->next;
            right = right->next;
        } 

        reverseList(half); //反转后半部分， 复原链表

        return true;
    }

    void reverse() //反转链表
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

    std::unordered_map<T, int> buildDiction() //建立字典
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

    void clear() //清空链表
    {
        ListNode<T>* cur = head;
        while (head)
        {
            ListNode<T>* temp = head->next;
            delete head;
            head = temp;
        }
    }

    void inputFromFile(const std::wstring &filename)
    {
        clear();

        std::wstring text = readFileToWString(filename);
        if (text.empty()) {
            std::wcerr << L"无法读取文件或文件为空: " << filename << std::endl;
            return;
        }

        std::wstring word;
        for (wchar_t ch : text) {
            if (iswpunct(ch) || iswspace(ch) || isChinesePunct(ch)) {
                if (!word.empty()) {
                    append(word);
                    word.clear();
                }
            } else {
                word += ch;
            }
        }
        if (!word.empty()) append(word);

        std::wcout << L"文件读取并分词完成 ✅" << std::endl;
    }


    ~LinkedList() { clear(); }
};




int main(int argc, char *argv[])
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    setlocale(LC_ALL, ""); // 设置本地化支持

    LinkedList<std::wstring> list;
    std::wcout << L"====== 字符串操作 ======" << std::endl;
    std::wcout << L"操作 a.在终端输入文本 b.从文件读取文本" << std::endl;

    std::wstring choice;
    std::getline(std::wcin, choice); // 用 wcin 读

    if (choice == L"a" || choice == L"A") {
        list.input();
    } else if (choice == L"b" || choice == L"B") {
        std::wcout << L"请输入文件路径：" << std::endl;
        std::wstring filepath;
        std::wcin >> filepath;
        list.inputFromFile(filepath);
    } else {
        std::wcout << L"无效输入" << std::endl;
    }

    int k = 0;


    std::wcout << L"1:输出当前内容" << std::endl
              << L"2:插入词" << std::endl
              << L"3:删除词" << std::endl
              << L"4:倒置当前字符串" << std::endl
              << L"5:判断当前字符串是否是回文串" << std::endl
              << L"6:计算当前词数" << std::endl
              << L"7:查找某个字符串是否存在" << std::endl
              << L"8:销毁当前字符串" << std::endl
              << L"9:生成词典" << std::endl
              << L"-1:退出操作" << std::endl;
    
    while (k != -1)
    {
        std::wcout << L"请选择你想进行的操作：" << std::endl;
        while (!(std::wcin >> k))
        {
            std::wcin.clear(); 
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
            std::wcout << L"请输入你要插入的词" << std::endl;
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
            std::wcout << L"请输入你要删除的词的位置索引" << std::endl;
            std::wcin >> index;
            list.remove(index);
            break;
        }

        case 4:
        {
            list.reverse();
            std::wcout << L"已完成反转，反转后的文本为：" << std::endl;
            list.print();
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

            std::wstring line;
            std::vector<std::wstring> words;

            std::getline(std::wcin >> std::ws, line);

            std::wistringstream iss(line);
            std::wstring word;
            while (iss >> word) {
                words.push_back(word);
            }

            bool b = list.findSeq(words); 
            std::wcout << (b ? L"存在" : L"不存在") << std::endl;
            break;
        }


        case 8:
        {
            list.clear();
            std::wcout << L"该文本已被销毁" << std::endl;
            break;
        }

        case 9:
        {
            std::unordered_map<std::wstring, int> diction = list.buildDiction();
            for (auto it = diction.begin(); it != diction.end(); ++it)
                std::wcout << it->first << L": " << it->second << std::endl;
            break;
        }
        case -1:
            return 0;
        default:
            std::wcout << L"ERROR:选项无效。" << std::endl;
            break;
        }
        std::wcout << std::endl;
    }
}
