// 61. Rotate List.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) 
	{
		if (!head || !head->next)
		{
			return head;
		}
		ListNode *h = new ListNode(0);
		h->next = head;
		head = h;

		ListNode* p = head->next;
		ListNode* q = p;
		int kk = k;

		while (kk--)
		{
			if (p->next)
			{
				p = p->next;
			}
			else
			{
				break;
			}
		}
		cout << "KK: " << kk << endl;
		if (0 == kk)
		{
			return head->next;
		}

		q = head->next;
		cout << "p->val: " << p->val << endl;
		cout << "q->val: " << q->val << endl;
		while (p->next)
		{
			p = p->next;
			q = q->next;
		}

		cout << "p->val: " << p->val << endl;
		cout << "q->val: " << q->val << endl;

		p->next = head->next;
		head->next = q->next;
		q->next = nullptr;
		this->printList(head);

		head = head->next;
		delete h;
		return head;
	}
	/*
	可以考虑先将链表连成一个环，然后从中找到相应位置把环解开
	*/
	ListNode* rotateRightAnswer(ListNode* head, int k)
	{
		if (!head || !head->next)
		{
			return head;
		}
		int length = 1;
		ListNode *p = head;
		while (p->next)
		{
			p = p->next;
			++length;
		}
		cout << "Length: " << length << endl;
		p->next = head;
		// 		if (k %= length)
		// 		{
		// 			for (auto i = 0; i<length - k; i++) 
		// 				p = p->next; // the tail node is the (len-k)-th node (1st node is head)
		// 		}
		int dist = abs(length - k % length);
		for (int i = 0; i < dist; ++i)
		{
			p = p->next;
		}
		head = p->next;
		p->next = nullptr;
		return head;
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

FILE *stream;

int main()
{
	Solution s;
	freopen_s(&stream, "../../input.txt", "r", stdin);
	int k = 0;
	int n = 0;
	int tmp = 0;
	while (cin >> k >> n)
	{
		cout << "--------------------------" << endl;
		ListNode *head = new ListNode(0);
		ListNode *q = head;
		for (int i = 0; i != n; ++i)
		{
			cin >> tmp;			
			ListNode* newNode = new ListNode(tmp);
			newNode->next = nullptr;
			q->next = newNode;
			q = q->next;
		}
		s.printList(head->next);
		head->next = s.rotateRightAnswer(head->next, k);
		s.printList(head->next);
		while (head)
		{
			q = head;
			head = q->next;
			delete q;
		}
	}
	fclose(stream);
    return 0;
}

