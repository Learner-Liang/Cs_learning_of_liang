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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。

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
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	while (~scanf("%s", s))
	{
		if (strcmp(s, "end")==0)break;
		insert(h, s);
		memset(s, 0, 100);
	}
	out_put(h);
	while (~scanf("%s", s))
	{
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		if (find(h, s))printf("ҵ%s\n", s);
		else
			printf("ûҵ\n");
		memset(s, 0, 100);
	}
	//¡
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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
	// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
	// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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