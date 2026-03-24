/*
【题目】排序链表
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

#include <iostream>
#include <vector>
using namespace std;
//typedef struct ListNode {
//	int val;
//	ListNode* next;
//}ListNode;
//ListNode* sortList(ListNode* head)
//{
//	if(head==NULL||head->next==NULL)
//	return head;
//	//¹һ
//	ListNode* p=head,* q , * h1=NULL, *h2=NULL;
//	int l = p->val, r = p->val, z;
//	while (p)
//	{
//		l = min(p->val, l);
//		r = max(p->val, r);
//		p = p->next;
//	}
//	if (l == r) return head;
//	z = (l + r) >> 2;
//	p = head;
//	while (p)
//	{
//		q = p->next;
//		if (p->val <= z)
//		{
//			p->next = h1;
//			h1 = p;
//		}
//		else {
//			p->next = h2;
//			h2 = p;
//		}
//		p = q;
//	}
//	h1 = sortList(h1);
//	h2 = sortList(h2);
//	q = h1;
//	while (q->next)
//	{
//		q = q->next;
//	}
//	q->next = h2;
//	return h1;
//}
//int getLength(ListNode* head) {
//	int n = 0;
//	while (head) n += 1, head = head->next;
//	return n;
//}
//ListNode* merge_sort(ListNode* head, int n) {
//	if (n <= 1) return head;
//	int l = n / 2, r = n - l;
//	ListNode* p = head, * p1, * p2, ret;
//	for (int i = 1; i < l; i++) p = p->next;
//	p1 = head; p2 = p->next;
//	p->next = NULL;
//	p1 = merge_sort(p1, l);
//	p2 = merge_sort(p2, r);
//	p = &ret; ret.next = NULL;
//	while (p1 || p2) {
//		if (p2 == NULL || (p1 && p1->val <= p2->val)) {
//			p->next = p1;
//			p = p1;  
//			p1 = p1->next;
//		}
//		else {
//			p->next = p2;
//			p = p2;
//			p2 = p2->next;
//		}
//	}
//	return ret.next;
//}
//ListNode* sortList(ListNode* head) {
//	int n = getLength(head);
//	return merge_sort(head, n);
//}
int main2()
{
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	/*ListNode head, tail;
	head.val = 5;
	head.next = &tail;
	tail.val = 6;
	tail.next = NULL;
	sortList(&head);*/

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
//Ҳù鲢
//88
//Ӻǰ 