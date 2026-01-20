struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (!list1) return list2;
        if (!list2) return list1;

        ListNode *newHead = new ListNode(0);
        ListNode *cur = newHead;

        while (list1 && list2) {
            if (list1->val == list2->val) {
                cur->next = new ListNode(list1->val);
                cur->next->next = new ListNode(list2->val);
                cur = cur->next->next;
                list1 = list1->next;
                list2 = list2->next;
            } else if (list1->val < list2->val) {
                cur->next = new ListNode(list1->val);
                cur = cur->next;
                list1 = list1->next;
            } else {
                cur->next = new ListNode(list2->val);
                cur = cur->next;
                list2 = list2->next;
            }
        }

        if (list1)
            cur->next = list1;
        
        if (list2)
            cur->next = list2;

        return newHead->next;
    }
};