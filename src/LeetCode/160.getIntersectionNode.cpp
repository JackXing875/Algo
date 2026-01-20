#include <unordered_set>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* temp = headA;
        std::unordered_set<ListNode*> visited;

        while (temp) {
            visited.insert(temp);
            temp = temp->next;
        }

        temp = headB;

        while (temp) {
            if (visited.find(temp) != visited.end()) 
                return temp;
            temp = temp->next;
        }

        return nullptr;
    }
};