/*
【题目】13 线段树的编码技巧——动态开点
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

//为了使用完全二叉树，会开辟4*n-1个节点，但是实际上只要2n个
#include <iostream>
using namespace std;
//用模板1演示
//​ 操作1：修改数组中某个位置的值
//
//​ 操作2：查询数组中某个区间的最大值
struct Node
{
	int c, l, r;
};
int node_cnt = 1;
void build_tree(Node* tree,int* a, int ind, int l, int r);
void updata(Node* tree, int ind);
void modify(Node* tree, int ind,int l,int r, int b, int c);
int query(Node* tree, int ind,int l, int r, int x, int y);
int main13()
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

	Node tree[100];//2n个节点
	int a[100];
	int n, m;
	cin >> n >> m;
	for (int i = 1;i <= n;i++)cin >> a[i];
	build_tree(tree, a, 1, 1, n);
	for (int i = 0, a, b, c;i < m;i++)
	{
		cin >> a >> b >> c;
		if (a == 1)
		{
			if (b <= c)modify(tree, 1,1,n, b, c);
		}
		else
		{
			if (b <= c)cout << query(tree,1,1,n,b,c) << endl;
		}
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void build_tree(Node* tree,int* a , int ind, int l, int r)
{
	if (l == r)
	{
		tree[ind].c = a[l];
		return;
	}
	int mid = (l + r) / 2;
	tree[ind].l = ++node_cnt;
	tree[ind].r = ++node_cnt;
	build_tree(tree, a, tree[ind].l, l, mid);
	build_tree(tree, a, tree[ind].r, mid + 1,r);
	updata(tree, ind);
	return;
}
void updata(Node* tree, int ind)
{
	tree[ind].c = max(tree[tree[ind].l].c, tree[tree[ind].r].c);
	return;
}
void modify(Node* tree, int ind, int l, int r ,int b, int c)
{
	if (l == r)
	{
		tree[ind].c = c;
		return;
	}
	int mid = (l + r) / 2;
	if (b <= mid)
		modify(tree, tree[ind].l, l, mid, b, c);
	else
		modify(tree, tree[ind].r, mid + 1, r, b, c);
	updata(tree, ind);
	return;
}
int query(Node* tree, int ind, int l, int r, int x, int y)
{
	if (x <= l && y >= r)
		return tree[ind].c;
	int ans = -22222222;
	int mid = (l + r) / 2;
	if (x <= mid)ans = max(ans, query(tree, tree[ind].l, l, mid, x, y));
	if (y > mid)ans = max(ans, query(tree, tree[ind].r, mid + 1, r, x, y));
	return ans;
}