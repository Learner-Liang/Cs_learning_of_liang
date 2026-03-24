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
int max(int a, int b);
Node* maintain(Node* root);
Node* left_rotated(Node* root);
Node* right_rotated(Node* root);
Node* erase(Node* root, int val);
Node* pre_Node(Node* root);
Node* find(Node* root, int val);
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

	srand(time(NULL));
	Node* root = &NIL;
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

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void out_put(Node* root)
{
	if (root == &NIL)return;
	out_put(root->left);
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