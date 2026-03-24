/*
【题目】3 哈希表与布隆过滤器
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

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct Node {
	char* s;
	struct Node* next;
}Node;
typedef struct Hash_table {
	Node* data;
	int size;
	int count;//Ԫ
}Hash_table;
Node* getNewNode(char* s);
Hash_table* getNewHash(int n);
void clearHash(Hash_table* h);
void clearNode(Node* p);
int insert(Hash_table* h, const char* s);
int hash_func(const char* s);
int find(Hash_table* h, const char* s);
void out_put(Hash_table* h);
void expand(Hash_table* h);
void swapHash(Hash_table* h,Hash_table* new_h);
void swap(int* a, int* b);
//ϣģunordered_mapunorder_set
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

	//ϣԪ䵽ĺ
	//ϣӸάռ䵽άռ䣬ԪൽԪ
	//ͻ
	//Ŷַ
	//ٹϣ
	//
	//ʽַ
	srand(time(0));
	Hash_table* h = getNewHash(2);
	char s[100] = { 0 };
	while (~scanf("%s", s))
	{
		if (strcmp(s, "end")==0)break;
		insert(h, s);
		memset(s, 0, 100);
	}
	out_put(h);
	while (~scanf("%s", s))
	{
		if (find(h, s))printf("ҵ%s\n", s);
		else
			printf("ûҵ\n");
		memset(s, 0, 100);
	}
	//¡

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
Node* getNewNode(char* s)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->s = _strdup(s);
	p->next = NULL;
	return p;
}
Hash_table* getNewHash(int n)
{
	Hash_table* p = (Hash_table*)malloc(sizeof(Hash_table));
	p->size = n;
	p->data = (Node*)malloc(sizeof(Node)*n);
	for (int i = 0;i < n;i++)p->data[i].next = NULL;//Ĭϳʼ
	p->count = 0;
	return p;
}
void clearHash(Hash_table* h)
{
	if (h == NULL)return;
	for (int i = 0;i < h->size;i++)
	{
		Node* p = h->data[i].next, * q;
		while (p)
		{
			q = p->next;
			/*free(p->s);
			free(p);*/
			clearNode(p);
			p = q;
		}
	}
	free(h->data);
	free(h);
}
void clearNode(Node* p)
{
	if (p == NULL)return;
	if(p->s)free(p->s);
	free(p);
	return;
}
int hash_func(const char* s)
{
	int seed = 131, h = 0;
	for (int i = 0;s[i];i++)
	{
		h = h * seed + s[i];
	}
	return h & 0x7fffffff;//õ
}

int insert(Hash_table* h, const char* s)
{
	//ж
	if (h->count >= h->size * 2) {
		expand(h);
	}
	int hcode = hash_func(s), ind = hcode % h->size;//ַϣֵ
	Node* p = getNewNode(s);
	//ʱͷЧʸ
	p->next = h->data[ind].next;
	h->data[ind].next = p;
	h->count += 1;
	return 1;
}
int find(Hash_table* h, const char* s)
{
	int ind = hash_func(s) % h->size;
	Node* p = h->data[ind].next;
	while (p)
	{
		if (strcmp(p->s, s)==0) return 1;
		p = p->next;
	}
	return 0;
}
void out_put(Hash_table* h)
{
	Node* p;
	for (int i = 0;i < h->size;i++)
	{
		p = h->data[i].next;
		while (p)
		{
			printf("%s ->  ", p->s);
			p = p->next;
		}
		printf("\n");
	}
	return ;
}
void expand(Hash_table* h)
{
	Hash_table* new_h = getNewHash(2 * h->size);
	for (int i = 0;i < h->size;i++)
	{
		Node* p = h->data[i].next;
		while (p)
		{
			insert(new_h, p->s);
			p = p->next;
		}
	}
	swapHash(h, new_h);
	clearHash(new_h);
	return ;
}
void swapHash(Hash_table* h, Hash_table* new_h)
{
	swap(&h->size, &new_h->size);
	swap(&h->count, &new_h->count);
	Node* temp = h->data;
	h->data = new_h->data;
	new_h->data = temp;
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}