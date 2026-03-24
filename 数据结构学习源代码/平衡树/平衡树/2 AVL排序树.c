/*
【题目】2 AVL排序树
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


//ʱ˻ΪAVL
//ĸ߶ƣĸ߶ȲС1
//עƽ
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int val;
	Node* left, * right;
	int height;
}Node;
Node NIL = { -1,&NIL,&NIL,0 };
void out_put(Node* root);
Node* getNewNode(int val);
void clear(Node* root);
Node* insert(Node* root, int val);
void update_height(Node* root);
// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

int max(int a, int b);
Node* maintain(Node* root);
Node* left_rotated(Node* root);
Node* right_rotated(Node* root);
Node* erase(Node* root, int val);
Node* pre_Node(Node* root);
Node* find(Node* root, int val);
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

	srand(time(NULL));
	Node* root = &NIL;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;i < 10;i++)
	{
		root = insert(root, rand() % 30);
	}
	out_put(root);
	int val = 1;
	while (val)
	{
		scanf("%d", &val);
		if (val == 1)root = insert(root, rand() % 30);
		else if (val == 2)root = erase(root, rand() % 30);
		out_put(root);
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}
void out_put(Node* root)
{
	if (root == &NIL)return;
	out_put(root->left);
	
	// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
	printf(" %d ", root->val);
	out_put(root->right);
	return;
}
Node* getNewNode(int val)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->val = val;
	temp->left = &NIL;
	temp->right = &NIL;
	temp->height = 1;
	return temp;
}
void clear(Node* root)
{
	if (root == &NIL)return;
	clear(root->left);
	clear(root->right);
	free(root);
	return;
}
Node* insert(Node* root, int val)
{
	if (root == &NIL)return getNewNode(val);
	if (root->val == val)return root;
	else if (root->val < val)root->right = insert(root->right, val);
	else root->left = insert(root->left, val);
	update_height(root);
	return maintain(root);
}
void update_height(Node* root)
{
	root->height = max(root->left->height, root->right->height) + 1;
	return;
}
int max(int a, int b)
{
	return a > b ? a : b;
}
Node* maintain(Node* root)
{
	if (abs(root->left->height - root->right->height) <= 1)return root;
	if (root->left->height > root->right->height)
	{
		if (root->left->left->height > root->left->right->height)
		{
			return right_rotated(root);
		}
		else
		{
			root->left = left_rotated(root->left);
			return right_rotated(root);
		}
	}
	else
	{
		if (root->right->right->height > root->right->left->height)
		{
			return left_rotated(root);
		}
		else
		{
			root->right = right_rotated(root->right);
			return left_rotated(root);
		}
	}
}
Node* left_rotated(Node* root)
{
	Node* r = root->right;
	root->right = r->left;
	r->left = root;
	update_height(r->left);
	//update_height(r->right);
	update_height(r);
	return r;
}
Node* right_rotated(Node* root)
{
	Node* l = root->left;
	root->left = l->right;
	l->right = root;
	update_height(root);
	update_height(l);
	return l;
}
Node* erase(Node* root, int val)
{
	if (root == &NIL)return root;
	if (root->val < val)
	{
		root->right = erase(root->right, val);
	}
	else if (root->val > val)
	{
		root->left = erase(root->left, val);
	}
	else
	{
		if ((root->left == &NIL) && (root->right == &NIL))
		{
			free(root);
			return &NIL;
		}
		else if (root->left == &NIL || root->right == &NIL)
		{
			Node* t = root->left == &NIL ? root->right : root->left;
			free(root);
			return t;
		}
		else
		{
			Node* p = pre_Node(root);
			root->val = p->val;
			root->left = erase(root->left, p->val);
		}
	}
	update_height(root);
	return maintain(root);
}
Node* pre_Node(Node* root)
{
	Node* temp = root->left;
	while (temp->right != &NIL)
	{
		temp = temp->right;
	}
	return temp;
}
Node* find(Node* root, int val)
{
	if (root == &NIL)return &NIL;
	if (root->val < val)return find(root->right, val);
	else if (root->val > val)return find(root->left, val);
	else return root;
}