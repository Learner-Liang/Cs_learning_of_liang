#include <iostream>
#include <cmath>
#include <string>

using namespace std;
typedef struct Node {
	Node* next[26];
	int color=0;
}Node;
typedef struct DANode {
	int base, check;
}DANode;
Node* getNewNode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	for (int i = 0;i < 26;i++)
		p->next[i] = NULL;
	p->color = 0;
	return p;
}
DANode trie[100005];
int da_root = 1;
void clear(Node* root)
{
	if (root == NULL)return;
	for (int i = 0;i < 26;i++)
		clear(root->next[i]);
	free(root);
	return;
}
void insert(Node* root,const char* s)
{
	Node* p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (p->next[ind] == NULL)p->next[ind] = getNewNode();
		p = p->next[ind];
	}
	p->color = 1;
	return;
}
bool find(Node* root, const char* s)
{
	Node* p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		p = p->next[ind];
		if (p== NULL)return false;
	}
	return p->color;
}

void output(Node* root, int n, string s)
{
	s[n] = 0;
	if (root->color)cout << s << endl;
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i] == NULL)continue;
		s[i] = 'a' + i;
		output(root->next[i], 1, s);
	}
	return;  
}
//红色表示字典中有这个词，把对应节点标记为红色
//每条边对应一个字母
//节点表示以某个字符为前缀的单词的集合
//边表示关系，即前缀是某个字符的单词
//双数组字典树
// 
//结构相同，但是信息表示方式不一样
// //要存储的信息
//当前节点的子节点信息
//当前节点是否成词
//通过check的正负性判断是否独立成词
int getBase(Node* root, int ind, DANode* trie)
{
	int base = 2;
	do
	{
		int flag = 1;
		for (int i = 0;i < 26;i++)
		{
			if (root->next[i] == NULL)continue;
			if (trie[ind + i].check == 0)continue;
			flag = 0;
		}
		if (flag)
			break;
		base++;
	} while (1);
		return base;
}
void convert_to_double_array(Node* root, int ind, DANode* trie)
{
	trie[ind].base = getBase(root, ind, trie);
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i] == NULL)continue;
		trie[trie[ind].base+i].check = (root->color ? -ind : ind);
	}
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i] == NULL)continue;
		convert_to_double_array(root->next[i], trie[ind].base + i, trie);
	}
	return;
}
bool find_f_d_a(int ind, DANode* trie, char* s)
{
	int p = ind;
	for (int i = 0;s[i];i++)
	{
		int temp = s[i] - 'a';
		if (abs(trie[trie[ind].base + temp].check) == ind)
		{
			ind = trie[ind].base + temp;
			continue;
		}
		return false;
	}
	return trie[ind].check<0;
}
int main8()
{
	int op;
	int n = 0;//单词的数目
	char s[100] = { 0 };
	Node* root = getNewNode();
	do {
		cin >> op;
		op %= 3;
		cin >> s;
		switch (op) {
		case 1: {
			insert(root, s);
			printf("insert %s to tire\n", s);
			n++;
			break;
		}
		case 2: {
			printf("find %s from tire : ", s);
			cout << find(root, s) << endl;
			break;
		}
		case 3:break;
		}
	} while (1);
	convert_to_double_array(root, da_root, trie);
	clear(root);
	return 0;
}