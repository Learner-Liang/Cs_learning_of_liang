/*
【题目】8 tire 字典树  双数组字典树
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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	Node* p = (Node*)malloc(sizeof(Node));
	for (int i = 0;i < 26;i++)
		p->next[i] = NULL;
	p->color = 0;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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
//ɫʾֵʣѶӦڵΪɫ
//ÿ߶Ӧһĸ
//ڵʾĳַΪǰ׺ĵʵļ
//߱ʾϵǰ׺ĳַĵ
//˫ֵ
// 
//ṹͬϢʾʽһ
// //Ҫ洢Ϣ
//ǰڵӽڵϢ
//ǰڵǷɴ
//ͨcheckжǷɴ
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
	int n = 0;//ʵĿ
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