/*
【题目】3 二叉搜索树的全能通用模板
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
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <queue>
//#include <pair>
using namespace std;
typedef struct Node
{
	struct Node* left = NULL, * right = NULL;
	int val;
	int cnt = 1;
	int size = 1;
}Node;
Node* root1 = NULL;
Node* getNode1(Node* root, int val);
int preNode(Node* root, int x);
int lastNode(Node* root, int x);
int query(Node* root, int x);
int ratings(Node* root, int x, int ans);
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

	int q;
	cin >> q;
	for (int i = 0, x, y;i < q;i++)
	{
		scanf("%d %d", &x, &y);
		if (x == 5)root1 = getNode1(root1, y);
		else if (x == 4)
		{
			if (lastNode(root1, y) == 0)cout << "2147483647" << endl;
		}
		else if (x == 3)
		{
			if (root1->val >= y && root1->left == NULL)cout << "−2147483647" << endl;
			else preNode(root1, y);
		}
		else if (x == 2)query(root1, y);
		else if (x == 1)ratings(root1, y, 1);
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
Node* getNode(Node* root, int val) {

	if (root == NULL) {

		Node* newNode = (Node*)malloc(sizeof(Node));

		newNode->val = val;

		newNode->cnt = 1;

		newNode->size = 1;

		newNode->left = newNode->right = NULL;

		return newNode;

	}

	if (val < root->val) {

		root->left = getNode(root->left, val);

	}
	else if (val > root->val) {

		root->right = getNode(root->right, val);

	}
	else {

		root->cnt++;

	}

	// 更新当前节点的size为左子树size + 右子树size + 当前cnt

	root->size = root->cnt;

	if (root->left) root->size += root->left->size;

	if (root->right) root->size += root->right->size;

	return root;

}
Node* getNode1(Node* root, int val)
{
	if (root == NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));

		newNode->val = val;

		newNode->cnt = 1;

		newNode->size = 1;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
	if (val < root->val)
	{
		root->left = getNode(root->left, val);
	}
	else if (val > root->val)
	{
		root->right = getNode(root->right, val);
	}
	else
	{
		root->cnt++;
	}
	root->size = root->cnt;
	if (root->left) root->size += root->left->size;
	if (root->right) root->size += root->right->size;
	return root;
}
int preNode(Node* root, int x)
{
	if (root == NULL)return 0;
	if (root->val >= x)
	{
		return preNode(root->left, x);
	}
	else
	{
		if (root->right != NULL)
		{
			if (preNode(root->right, x) == 0)
			{
				cout << root->val << endl;
				return 1;
			}
			return 1;
		}
		else cout << root->val << endl;
		return 1;
	}
}
int lastNode(Node* root, int x)
{
	if (root == NULL)return 0;
	if (root->val <= x)
	{
		return (lastNode(root->right, x));
	}
	else
	{
		if (lastNode(root->left, x) == 0)
		{
			cout << root->val << endl;
			return 1;
		}
		return 1;
	}
}
int query(Node* root, int x)
{
	if (root->left == NULL)
	{
		if (x <= root->cnt)cout << root->val << endl;
		else query(root->right, x - root->cnt);
		return 0;
	}
	if (x <= root->left->size)
	{
		query(root->left, x);
		return 0;
	}
	else if (x <= root->left->size + root->cnt)
	{
		cout << root->val << endl;
		return 0;
	}
	else query(root->right, x - (root->left->size + root->cnt));
	return 0;
}
int ratings(Node* root, int x, int ans)
{
	if (root->val > x)
	{
		if (root->left == NULL)cout << ans << endl;
		else ratings(root->left, x, ans);
		return 0;
	}
	else if (root->val == x)
	{
		if (root->left != NULL)
		{
			ans += root->left->size;
			cout << ans << endl;
		}
		else cout << ans << endl;
		return 0;
	}
	else
	{
		if (root->left)ans += root->left->size;
		ans += root->cnt;
		if (root->right != NULL)ratings(root->right, x, ans);
		else cout << ans;

	}
	return 0;
}