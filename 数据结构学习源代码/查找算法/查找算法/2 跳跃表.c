#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Node {
	int key, level;//层数
	struct Node* right;
	struct Node* up, * down;
}Node;
typedef struct Skiplist {
	Node* head, * tail;
}Skiplist;
Skiplist* getNewSkiplist(int n);//最大层数
Node* getNewNode();
void clear(Skiplist* s);
void clearNode(Node* node);
Node* find(Skiplist* s,int x);
void insert(Skiplist* s, int val);
void _output(Skiplist* s);
int main()
{
	//适用于链表的数据查找
	//头节点为负无穷，尾节点为极大值
	//插入到跳跃表中的元素会维护有序性
	//下一位比查找值大向下找，比查找值小向右找
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