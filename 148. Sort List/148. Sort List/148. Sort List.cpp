// 148. Sort List.cpp : 定义控制台应用程序的入口点。
// Sort a linked list in O(n log n) time using constant space complexity.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

class Solution {
public:
	ListNode* sortList(ListNode* head) {

	}
	void printList(ListNode* head)
	{
		if (!head)
		{
			return;
		}
		ListNode* p = head;
		while (p)
		{
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}
};


int main()
{
    return 0;
}

