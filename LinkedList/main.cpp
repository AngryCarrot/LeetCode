#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// * Definition for singly-linked list with a random pointer.
struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /* 109. Convert Sorted List to Binary Search Tree
     * Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.
     * TODO:
     * */
    void sortedListToBST(ListNode* head)
    {
        while (head)
            head = head->next;
        return;
    }

    /** 82. Remove Duplicates from Sorted List II
     * @brief deleteDuplicates: Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list. Given 1->2->3->3->4->4->5, return 1->2->5. Given 1->1->1->2->3, return 2->3.
     * @param head
     * @return
     * 坑：1.可能正序也可能倒序
     *    2.如果加if判断为newHead赋值的话，会遇到整形溢出问题，最小负数-1，最大正数+1
     * Answer: 如果有相同的，那就一直走，直到找到下一个不同的结点
     */
    ListNode* deleteDuplicates2(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        ListNode newHead(0);
        newHead.next = head;
        ListNode *pPre = &newHead;
        ListNode *pCur = pPre->next;
        ListNode *pNext = nullptr;
        while (pCur)
        {
            pNext = pCur->next;
            if (pNext && pCur->val == pNext->val)
            {
                // Move pNext to the next different value
                while (pNext && pCur->val == pNext->val)
                {
                    // release the memory of pNext
                    pNext = pNext->next;
                }
                pCur = pNext;
                pPre->next = pCur;
            }
            else
            {
                pPre = pCur;
                pCur = pCur->next;
            }
        }
        return newHead.next;
    }

    /**  86. Partition List
     * @brief partition: Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x. You should preserve the original relative order of the nodes in each of the two partitions.
     * @param head
     * @param x
     * @return
     */
    ListNode* partition(ListNode* head, int x)
    {
        if (!head)
        {
            return head;
        }
        ListNode newHeadLess(0);
        ListNode newHeadBigger(0);
        ListNode *pCurLess = &newHeadLess;
        ListNode *pCurBigger = &newHeadBigger;
        while (head)
        {
            if (head->val < x)
            {
                pCurLess = pCurLess->next = head;
            }
            else
            {
                pCurBigger = pCurBigger->next = head;
            }
            head = head->next;
        }
        pCurBigger->next = nullptr;
        pCurLess->next = newHeadBigger.next;
        return newHeadLess.next;
    }

    /* 92. Reverse Linked List II
     * Reverse a linked list from position m to n. Do it in-place and in one-pass.
     * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
     * return 1->4->3->2->5->NULL.
     * 1 ≤ m ≤ n ≤ length of list.
     * 坑：for循环体多写了一次，currentIndex不能<=n
     * */
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        if (!head || !head->next || m == n)
        {
            return head;
        }
        ListNode *pNewHead = new ListNode(0);
        pNewHead->next = head;
        ListNode *pCurrentNode = pNewHead;
        int currentIndex = 1;
        while (currentIndex != m)
        {
            pCurrentNode = pCurrentNode->next;
            ++currentIndex;
        }
        ListNode *pNext = pCurrentNode->next->next;
        ListNode *pLast = pCurrentNode->next;
        // pit
        for (; currentIndex < n; ++currentIndex)
        {
            pLast->next = pNext->next;
            pNext->next = pCurrentNode->next;
            pCurrentNode->next = pNext;
            pNext = pLast->next;
        }
        head = pNewHead->next;
        delete pNewHead;
        return head;
    }

    /* 143. Reorder List
     *  Given a singly linked list L: L0→L1→…→Ln-1→Ln,
     * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
     * You must do this in-place without altering the nodes' values.
     * */
    void reorderList(ListNode* head)
    {
        if (!head || !head->next || !head->next->next)
        {
            return;
        }

        ListNode *p1 = head, *p2 = head->next;
        while (p2 && p2->next) {
            p1 = p1->next;
            p2 = p2->next->next;
        }

        ListNode *head2 = p1->next;
        p1->next = nullptr;

        p2 = head2->next;
        head2->next = nullptr;
        while (p2)
        {
            p1 = p2->next;
            p2->next = head2;
            head2 = p2;
            p2 = p1;
        }

        for (p1 = head, p2 = head2; p1; )
        {
            auto t = p1->next;
            p1 = p1->next = p2;
            p2 = t;
        }
    }
    /*
     * use Stack
     * 坑：中间结点pSlow的next指针未置为空导致死循环
     * */
    void reorderListStack(ListNode* head) {
            if (!head || !head->next || !head->next->next)
            {
                return;
            }
            stack<ListNode*> s;
            ListNode *pSlow = head;
            ListNode *pFast = head->next;
            while (pFast && pFast->next)
            {
                pFast = pFast->next->next;
                pSlow = pSlow->next;
            }
            pFast = pSlow->next;
            pSlow->next = nullptr;
            pSlow = pFast;
            while (pSlow)
            {
                s.push(pSlow);
                pSlow = pSlow->next;
            }
            pSlow = head;
            while (!s.empty())
            {
                pFast = s.top();
                s.pop();
                pFast->next = pSlow->next;
                pSlow->next = pFast;
                pSlow = pFast->next;
            }
        }

    /* 147. Insertion Sort List
     * Sort a linked list using insertion sort.
     * 坑：next指针未置为空导致死循环
     * */
    ListNode* insertionSortList(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *pNewHead = new ListNode(0);
        pNewHead->next = head;
        head = head->next;
        pNewHead->next->next = nullptr;

        while (head)
        {
            ListNode *pStep = pNewHead;
            ListNode *pHead = head;
            head = head->next;
            pHead->next = nullptr;
            while (pStep->next && pHead->val > pStep->next->val)
            {
                pStep = pStep->next;
            }
            pHead->next = pStep->next;
            pStep->next = pHead;
        }

        head = pNewHead->next;
        delete pNewHead;
        return head;
    }

    /* 138. Copy List with Random Pointer
      * A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null. Return a deep copy of the list.
      * */
    // 该版本内存溢出
    RandomListNode *cloneList(RandomListNode *head)
    {
        RandomListNode *pStep = head;
        while (pStep)
        {
            RandomListNode *newNode = new RandomListNode(pStep->label);
            newNode->next = pStep->next;
            pStep->next = newNode;
            pStep = newNode->next;
        }
        return head;
    }
    RandomListNode *setPointer(RandomListNode *head)
    {
        RandomListNode *pStep = head;
        while (pStep)
        {
            RandomListNode *pNewNode = pStep->next;
            if (pStep->random)
            {
                pNewNode->random = pStep->random->next;
            }
            pStep = pNewNode->next;
        }
        return head;
    }
    RandomListNode *splitList(RandomListNode *head)
    {
        RandomListNode *pNewHead = head->next;
        RandomListNode *pStep = head;
        RandomListNode *pNewStep = pNewHead;
        while (pStep)
        {
            pStep->next = pNewStep->next;
            pStep = pStep->next;
            pNewStep->next = pStep->next;
            pNewStep = pNewStep->next;
        }
        return pNewHead;
    }
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        if (!head)
        {
            return head;
        }
        cloneList(head);
        setPointer(head);
        return copyRandomList(head);
    }
    RandomListNode *copyRandomListAnswer(RandomListNode *head) {
        if (!head) return NULL;
        RandomListNode* run = head;
        /* Insert the copy of each node after it. */
        while (run)
        {
            RandomListNode* copy = new RandomListNode(run->label);
            copy->next = run->next;
            run->next = copy;
            run = run->next->next;
        }
        /* Set the random pointer for each copy. */
        run = head;
        while (run)
        {
            if (run->random)
                run->next->random = run->random->next;
            run = run->next->next;
        }
        /* Extract the copy list. */
        RandomListNode* new_head = new RandomListNode(0);
        RandomListNode* new_run;
        run = head;
        new_head->next = head->next;
        while (run)
        {
            new_run = run->next;
            run->next = new_run->next;
            if (run->next)
                new_run->next = new_run->next->next;
            run = run->next;
        }
        return new_head->next;
    }

    // 148. Sort List
    // 该版本超时
    ListNode* sortList(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* nn = new ListNode(0);
        nn->next = head;
        head = nn;

        ListNode* p = head->next->next;
        ListNode* q = head;
        ListNode* r = q->next;
        while (p)
        {
            q = head;
            while (q->next->val < p->val)
            {
                q = q->next;
            }
            if (q->next == p)
            {
                r = p;
                p = p->next;
                continue;
            }
            r->next = p->next;
            p->next = q->next;
            q->next = p;
            p = r->next;
        }

        head = head->next;
        delete nn;
        return head;
    }

    ListNode* merge(ListNode* head1, ListNode* head2)
    {
        if (!head1)
        {
            return head2;
        }
        if (!head2)
        {
            return head1;
        }
        ListNode* p = head1;
//        ListNode* q = head2;
        ListNode* result = new ListNode(0);
        p = result;
        while (head1 && head2)
        {
            if (head1->val < head2->val)
            {
                p->next = head1;
                head1 = head1->next;
            }
            else
            {
                p->next = head2;
                head2 = head2->next;
            }
            p = p->next;
        }
        if (head1)
        {
            p->next = head1;
        }
        if (head2)
        {
            p->next = head2;
        }
        p = result;
        result = result->next;
        delete p;
        return result;
    }
    ListNode* sortListAnswer(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* fast = head->next;
        ListNode* slow = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        fast = slow->next;
        slow->next = nullptr;
        return merge(sortListAnswer(head), sortListAnswer(fast));
    }

    // 328. Odd Even Linked List
    ListNode* reverse(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* p = head->next;
        ListNode* q = head;
        while (p->next)
        {
            q = p->next;
            p->next = q->next;
            q->next = head->next;
            head->next = q;
        }
        return head;
    }
    ListNode* insertHead(ListNode* head, ListNode* node)
    {
        node->next = head->next;
        head->next = node;
        return head;
    }

    /**The relative order inside both the even and odd groups should remain as it was in the input.
The first node is considered odd, the second node even and so on*/
    ListNode* oddEvenList(ListNode* head)
    {
        if (!head || !head->next || !head->next->next)
        {
            return head;
        }
        ListNode* nn = new ListNode(0);
        nn->next = head;
        head = nn;

        ListNode* p = head->next;
        ListNode* q = p->next;
        ListNode* r = q->next;
        bool flag = true;
        while (r->next)
        {
            if (flag)
            {
                q->next = r->next;
                r->next = p->next;
                p->next = r;
                p = p->next;
            }
            else
            {
                cout << q->val << endl;
                q = q->next;
            }
            r = q->next;
            flag = !flag;
        }
        cout << "flag: " << flag << endl;
        if (flag)
        {
            r->next = p->next;
            p->next = r;q->next = nullptr;
        }

        head = head->next;
        delete nn;
        return head;
    }
    // 445. Add Two Numbers II
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        if (!l1)
        {
            return l2;
        }
        if (!l2)
        {
            return l1;
        }
        stack<int> s1;
        stack<int> s2;
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        while (p1)
        {
            s1.push(p1->val);
            p1 = p1->next;
        }
        while (p2)
        {
            s2.push(p2->val);
            p2 = p2->next;
        }
        ListNode *head = new ListNode(0);
        ListNode *q = nullptr, *p = head;
        int x1, x2, sum, flag = 0;
        while (!s1.empty() && !s2.empty())
        {
            x1 = s1.top();
            x2 = s2.top();
            sum = x1 + x2 + flag;
            flag = sum / 10;
            q = new ListNode(sum % 10);
            q->next = p->next;
            p->next = q;
            s1.pop();
            s2.pop();
        }
        while (!s1.empty())
        {
            x1 = s1.top() + flag;
            flag = x1 / 10;
            q = new ListNode(x1 % 10);
            q->next = p->next;
            p->next = q;
            s1.pop();
        }
        while (!s2.empty())
        {
            x2 = s2.top() + flag;
            flag = x2 / 10;
            q = new ListNode(x2 % 10);
            q->next = p->next;
            p->next = q;
            s2.pop();
        }
        if (flag)
        {
            q = new ListNode(flag);
            q->next = p->next;
            p->next = q;
            p = p->next;
        }
        p = head;
        head = head->next;
        delete p;
        return head;
    }

    // 19. Remove Nth Node From End of List
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (!head)
        {
            return head;
        }
        if (!head->next && 1 == n)
        {
            delete head;
            return nullptr;
        }
        ListNode *ne = new ListNode(0);
        ne->next = head;
        head = ne;
        ListNode *p = head;
        ListNode *q = head;
        while (n--)
        {
            p = p->next;
        }
        while (p->next)
        {
            p = p->next;
            q = q->next;
        }
        p = q->next;
        q->next = p->next;
        delete p;
        head = head->next;
        delete ne;
        return head;
    }
    // 21. Merge Two Sorted Lists
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if (!l1)
        {
            return l2;
        }
        if (!l2)
        {
            return l1;
        }
        ListNode *n = new ListNode(0);
        ListNode *p = n;

        while (l1 && l2)
        {
            if (l1->val < l2->val)
            {
                p->next = l1;
                l1 = l1->next;
            }
            else
            {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }

        if (l1)
        {
            p->next = l1;
        }

        if (l2)
        {
            p->next = l2;
        }

        p = n->next;
        delete n;
        return p;
    }
    // 24. Swap Nodes in Pairs
    ListNode* swapPairs(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode *n = new ListNode(0);
        n->next = head;
        head = n;
        ListNode *p = head->next;
        ListNode *q = p->next;
        ListNode *r = n;
        while (p)
        {
            q = p->next;
            if (q)
            {
                r->next = q;
                p->next = q->next;
                q->next = p;
            }
            r = p;
            p = p->next;
        }
        head = head->next;
        delete n;
        return head;
    }
    // 83. Remove Duplicates from Sorted List
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (!head)
        {
            return nullptr;
        }
        if (!head->next)
        {
            return head;
        }
        ListNode *p = head;
        ListNode *q = head;
        while (p)
        {
            q = p->next;
            if (!q)
            {
                return head;
            }
            if (p->val == q->val)
            {
                p->next = q->next;
                delete q;
            }
            else
            {
                p = p->next;
            }
        }
        return head;
    }
    // 142. Linked List Cycle II
    // Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
    ListNode *detectCycle(ListNode *head)
    {
        if (!head)
        {
            return nullptr;
        }
        ListNode *p1 = head;
        ListNode *p2 = head;
        while (p1)
        {
            p1 = p1->next;
            if (p2 && p2->next)
            {
                p2 = p2->next->next;
            }
            else
            {
                return nullptr;
            }
            if (p1 == p2)
            {
                p1 = head;
                break;
            }
        }
        while (p1 != p2)
        {
            p1 = p1->next;
            p2 = p2->next;
        }
        return p1;
    }
    // 141. Linked List Cycle
    bool hasCycle(ListNode *head)
    {
        if (!head)
        {
            return false;
        }
        ListNode *p1 = head;
        ListNode *p2 = head;
        while (p1)
        {
            p1 = p1->next;
            if (p2 && p2->next)
            {
                p2 = p2->next->next;
            }
            else
            {
                return false;
            }
            if (p1 == p2)
            {
                return true;
            }
        }
        return false;
    }
    // Intersection of Two Linked Lists
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (!headA || !headB)
        {
            return nullptr;
        }
        int lengthA = 1;
        ListNode* pA = headA;
        while (pA->next)
        {
            pA = pA->next;
            ++lengthA;
        }
        int lengthB = 1;
        ListNode* pB = headB;
        while (pB->next)
        {
            pB = pB->next;
            ++lengthB;
        }
        if (pA == pB)
        {
            pA = headA;
            pB = headB;
            int d = 0;
            if (lengthA > lengthB)
            {
                d = lengthA - lengthB;
            }
            else
            {
                d = lengthB - lengthA;
                pA = headB;
                pB = headA;
            }
            while (d--)
            {
                pA = pA->next;
            }
            while (pA != pB)
            {
                pA = pA->next;
                pB = pB->next;
                ++d;
            }
            if (d == lengthA || d == lengthB)
            {
                return nullptr;
            }
            else
            {
                return pA;
            }
        }
        else
        {
            return nullptr;
        }
    }
    ListNode* reverseList(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* p = head;
        ListNode* q = head;
        while (head->next)
        {
            q = head->next;
            head->next = q->next;
            q->next = p;
            p = q;
        }
        head = p;
        return p;
    }

    ListNode* findMiddleNode(ListNode* head)
    {
        if (!head || !head->next)
        {
            return head;
        }
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast)
        {
            fast = fast->next;
            if (fast && fast->next)
            {
                fast = fast->next;
                slow = slow->next;
            }
            else
            {
                break;
            }
        }
        return slow;
    }

    bool isPalindrome(ListNode* head)
    {
        if (!head || !head->next)
        {
            return true;
        }
        ListNode* mid = this->findMiddleNode(head);
        mid->next = this->reverseList(mid->next);
        ListNode* p = head, *q = mid->next;
        while (q)
        {
            if (q->val != p->val)
            {
                return false;
            }
            q = q->next;
            p = p->next;
        }
        return true;

    }
};

void printListNode(ListNode* head);
void deleteNode(ListNode* head);
int main()
{
    Solution s;
    ListNode* head = new ListNode(1);
    ListNode* p1 = new ListNode(3);
    ListNode* p2 = new ListNode(2);
    ListNode* p3 = new ListNode(4);
    ListNode* p4 = new ListNode(8);
    ListNode* p5 = new ListNode(9);
    ListNode* p6 = new ListNode(7);
    head->next = p1;
    p1->next = p2;
    p2->next = p3;
    p3->next = p4;

    //    ListNode* h2 = p4;
    p4->next = p5;
    p5->next = p6;
    printListNode(head);
    //    printListNode(h2);

    ListNode *h3 = s.insertionSortList(head);

    //    printListNode(head);
    //    printListNode(h2);
    printListNode(h3);

    deleteNode(head);
    //    deleteNode(h2);
    //    deleteNode(h3);
    return 0;
}


void printListNode(ListNode* head)
{
    ListNode* p = head;
    while (p)
    {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}


void deleteNode(ListNode* head)
{
    ListNode *p1 = nullptr;
    while (head)
    {
        p1 = head->next;
        delete head;
        head = p1;
    }
}
