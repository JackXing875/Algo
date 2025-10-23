#include <queue>

class MyStack {
private:
    std::queue<int> q;
    int topElem;

public:
    MyStack() {}
    
    void push(int x) {
        q.push(x);
        topElem = x;
    }
    
    int pop() {
        if (q.empty()) return -1;

        if (q.size() == 1) {
            int res = q.front();
            q.pop();
            return res;
        }

        size_t size = q.size();
        for (size_t i = 1; i < size; i++) {
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
        
        int res = q.front();
        q.pop();

        if (!q.empty()) {
            topElem = q.back();
        }

        return res;
    }
    
    int top() {
        return topElem;
    }
    
    bool empty() {
        return q.empty();
    }
};