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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

	Node* next[26];
	int color=0;
}Node;
typedef struct DANode {
	int base, check;
}DANode;
Node* getNewNode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;i < 26;i++)
		p->next[i] = NULL;
	p->color = 0;
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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
	
	// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
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
		
		// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
		// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
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