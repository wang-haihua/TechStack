#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* merge(ListNode *l1, ListNode *l2){
        if(!l1 || !l2) return l1?l1:l2;
        ListNode dummy;
        ListNode *tail = &dummy;
        ListNode *p1 = l1, *p2 = l2;
        while(p1 && p2){
            if(p1->val < p2->val){
                tail->next = p1;
                p1 = p1->next; 
            }else{
                tail->next = p2;
                p2 = p2->next;
            }
            tail = tail->next;
        }
        tail->next = p1?p1:p2;
        return dummy.next;
    }

    ListNode* mergeSort(ListNode* head, ListNode* tail){
        if(!head) return head;
        if(head->next == tail){
            head->next = nullptr;
            return head;
        }

        ListNode *slow = head, *fast = head;
        // // 错误示范，会导致越界
        // while(fast&&fast->next){
        //     fast = fast->next->next;
        //     slow = slow->next;
        // }
        while(fast != tail){
            slow = slow->next;
            fast = fast->next;
            if(fast != tail){
                fast = fast->next;
            }
        }

        ListNode* mid = slow;

        return merge(mergeSort(head,mid),mergeSort(mid,tail));
    }

    ListNode* sortList(ListNode* head) {
        return mergeSort(head,nullptr);
    }
};

int main(){
    vector<int> nodes{4,2,1,3};
    ListNode head;
    ListNode* tail = &head;
    for(const auto node: nodes){
        ListNode* n = new ListNode(node);
        tail->next = n;
        tail = n;
    }
    Solution s;
    s.sortList(head.next);
    return 0;
}