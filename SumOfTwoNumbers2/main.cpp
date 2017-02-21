#include <iostream>
#include <stack>
using namespace std;

//*Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

 class Solution {
 public:
     /*11 line result*/
     ListNode* addTwoNumbers(ListNode *l1, ListNode *l2, int)
     {
         ListNode preHead(0), *p = &preHead;
         int extra = 0;
         while (l1 || l2 || extra)
         {
             int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
             extra = sum / 10;
             p->next = new ListNode(sum % 10);
             p = p->next;
             l1 = l1 ? l1->next : l1;
             l2 = l2 ? l2->next : l2;
         }
         return preHead.next;
     }

     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
         ListNode *pl1 = l1, *pl2 = l2;
         ListNode *result = new ListNode(0);
         ListNode *pl = result;
         int flag = 0;
         while (pl1 && pl2)
         {
             int r = pl1->val + pl2->val + flag;
             ListNode *p = new ListNode(r % 10);
             flag = r / 10;
             pl->next = p;
             pl = p;
             pl1 = pl1->next;
             pl2 = pl2->next;
         }
         while (pl1)
         {
             int r = pl1->val + flag;
             ListNode *p = new ListNode(r % 10);
             flag = r / 10;
             pl->next = p;
             pl = p;
             pl1 = pl1->next;
         }
         while (pl2)
         {
             int r = pl2->val + flag;
             ListNode *p = new ListNode(r % 10);
             flag = r / 10;
             pl->next = p;
             pl = p;
             pl2 = pl2->next;
         }
         if (flag)
         {
             ListNode *p = new ListNode(flag);
             pl->next = p;
             pl = p;
         }
         pl = result;
         result = result->next;
         delete pl;
         return result;
     }
 };

int main()
{
    cout << "Hello World!" << endl;
    ListNode *l1 = nullptr;
    ListNode *l11 = new ListNode(8);
    ListNode *l12 = new ListNode(6);
//    ListNode *l13 = new ListNode(3);
    l1 = l11;
    l11->next = l12;
//    l12->next = l13->next;
    ListNode *l2 = nullptr;
    ListNode *l21 = new ListNode(6);
    ListNode *l22 = new ListNode(4);
    ListNode *l23 = new ListNode(8);
    l2 = l21;
    l21->next = l22;
    l22->next = l23->next;

    Solution s;
    ListNode *p = nullptr;    
    p = s.addTwoNumbers(l1, l2);
    ListNode *q = p;
    while (p)
    {
        cout << p->val << endl;
        p = p->next;
    }
    while (q)
    {
        p = q->next;
        delete q;
        q = p;
    }
    return 0;
}

