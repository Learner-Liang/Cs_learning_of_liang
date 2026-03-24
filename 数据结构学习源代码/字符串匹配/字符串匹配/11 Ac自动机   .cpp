#include <iostream>
#include <queue>
using namespace std;
//树中存储的是单词，用文本串进行匹配
//等价匹配指针，默认建立在根节点的位置
typedef struct Node {
	int flag;
	Node* next[26];
	Node* fail;
	//若是要输出单词，则此处应该加上一个字符串的定义
}Node;
//在一个文本串中找字典树中的模式串
//用多个模式串构建字典树AC自动机
//匹配前缀
Node* getNode_ac()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->flag = 0;
	p->fail = NULL;
	for (int i = 0;i < 26;i++)
	{
		p->next[i] = NULL;
	}
	return p;
}
void clear_ac(Node* p)
{
	if (p == NULL)return;
	for (int i = 0;i < 26;i++)
	{
		clear_ac(p->next[i]);
	}
	free(p);
}
void insert_ac(Node* root, const char* s)
{
	Node* p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (p->next[ind] == NULL)p->next[i] = getNode_ac();
		p = p->next[ind];
	}
	p->flag = 1;
	return;
}
void build_ac(Node* root)
{
	queue<Node*>q;
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i] == NULL)continue;
		root->next[i]->fail=root;
		q.push(root->next[i]);

	}
	while (!q.empty())
	{
		Node* temp = q.front(), * p;
		q.pop();
		for (int i = 0;i < 26;i++)
		{
			if (temp->next[i] == NULL)continue;
			//修改
			/*
			* if(temp==root)temp->next[i]=root;
			* else
			 temp->next[i]=temp->fail->next[i];前面已经完成了线索化，无需循环
			 continue;
			*/
			p = temp->fail;
			while (p && p->next[i] == NULL)p=p->fail;//此处也无需
			if (p == NULL)p = root;
			else p = p->next[i];
			temp->next[i]->fail = p;
			q.push(temp->next[i]);
		}
	}
}
void find_ac(Node* root, const char* s)
{
	Node* p = root, * q;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		while (p && p->next[ind] == NULL)p = p->fail;

		if (p == NULL)p = root;
		else p = p->next[ind];
		//上面三行改为 p = p->next[ind];
		q = p;
		//此处可以加入判断是否成词语并且输出字符串
	}
}
//线索优化
//直接指向要跳到的目标节点
int main11()
{

	return 0;
}