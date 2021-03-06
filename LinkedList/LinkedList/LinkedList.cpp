// LinkedList.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*** Definition for singly-linked list.*/
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) 
	{
		int i = 0;
		ListNode* current = head;
		while (current != nullptr && i != k)
		{
			current = current->next;
			++i;
		}
		if (i == k)
		{
			current = reverseKGroup(current, k);
			while (k-- > 0)
			{
				ListNode* tmp = head->next;
				head->next = current;
				current = head;
				head = tmp;
			}
			head = current;
		}
		return head;
	}
	ListNode* reverse(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr)
		{
			return head;
		}
		ListNode nh(0);
		ListNode* p = head;
		while (p != nullptr)
		{
			ListNode* q = nh.next;
			nh.next = p;
			ListNode* t = p->next;
			p->next = q;
			p = t;
		}
		return nh.next;
	}
};

int main()
{
    return 0;
}

