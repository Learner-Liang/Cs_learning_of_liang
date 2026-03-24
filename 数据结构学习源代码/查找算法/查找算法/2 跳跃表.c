/*
【题目】2 跳跃表
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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Node {
	int key, level;//
	struct Node* right;
	struct Node* up, * down;
}Node;
typedef struct Skiplist {
	Node* head, * tail;
}Skiplist;
Skiplist* getNewSkiplist(int n);//
Node* getNewNode();
void clear(Skiplist* s);
void clearNode(Node* node);
Node* find(Skiplist* s,int x);
void insert(Skiplist* s, int val);
void _output(Skiplist* s);
int main()
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

	//ݲ
	//ͷڵΪβڵΪֵ
	//뵽ԾеԪػά
	//һλȲֵңȲֵС
	srand(time(NULL));
	int x;
	Skiplist* s = getNewSkiplist(8);
	while (scanf_s("%d", &x))
	{
		if (x < 0)
			break;
		insert(s, x);
	}
	_output(s);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
Node* getNewNode(int key, int n)
{
	Node* p = (Node*)malloc(sizeof(Node)*n);
	for (int i = 0;i < n;i++)
	{
		p[i].key = key;
		p[i].right = NULL;
		p[i].down = (i? p+i-1:NULL);
		p[i].up = (i == n - 1 ? NULL : p + i);
		p[i].level = i;
	}
	return p + n - 1;
}
Skiplist* getNewSkiplist(int n)
{
	Skiplist* p = (Skiplist*)malloc(sizeof(Skiplist));
	p->head = getNewNode(-100000, n);
	p->tail = getNewNode(100000, n);
	Node* s1 = p->head, * s2 = p->tail;
	while(s1)
	{
		s1->right = s2;
		s1 = s1->down;
		s2 = s2->down;
	}
	return p;
}
void clear(Skiplist* s)
{
	Node* p = s->head;
	Node* q;
	while (p->down)
		p = p->down;
	while (p)
	{
		q = p->right;
		clearNode(p);
		p = q;
	}
	free(s);
	return;
}
void clearNode(Node* node)
{
	if (node == NULL)return;
	free(node);
	return;
}
Node* find(Skiplist* s,int x)
{
	Node* p = s->head;
	while (p && p->key != x)
	{
		if (x < p->right->key)   p = p->right;
		else if (x > p->right->key)     p = p->down;
		else if (x == p->right->key) return p->right;
	}
	return NULL;
}
void insert(Skiplist* s, int val)
{
	int n = rand() % 5+1;
	Node* p = getNewNode(val, n), * q = s->head;
	while (q->level != n-1)q = q->down;
	while(p)
	{
		while (val > q->right->key) q = q->right;
		p->right = q->right;
		q->right = p;
		p = p->down;
		q = q->down;
	}
	return;
}
void _output(Skiplist* s)
{
	Node* p = s->head;
	while (p->down)p = p->down;
	while (p)
	{
		printf("%d ->",p->key);
		p = p->right;
	}
	printf("\n");
}