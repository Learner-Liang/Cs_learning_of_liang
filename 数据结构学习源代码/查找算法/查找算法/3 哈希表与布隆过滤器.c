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
	int count;//元素数量
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
//哈希表的模拟用unordered_map或者unorder_set
int main()
{
	//哈希函数：将元素隐射到数组的函数
	//哈希：从高维空间到低维空间，即从元素数量多到元素数量少
	//冲突处理方法
	//开放定址
	//再哈希法
	//建立公共溢出区
	//链式地址
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
		if (find(h, s))printf("找到了%s\n", s);
		else
			printf("没找到\n");
		memset(s, 0, 100);
	}
	//布隆过滤器
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
	for (int i = 0;i < n;i++)p->data[i].next = NULL;//不会默认初始化
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
	return h & 0x7fffffff;//得到正数
}

int insert(Hash_table* h, const char* s)
{
	//判断扩容
	if (h->count >= h->size * 2) {
		expand(h);
	}
	int hcode = hash_func(s), ind = hcode % h->size;//计算字符串哈希值
	Node* p = getNewNode(s);
	//插入时放在链表头部效率更高
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