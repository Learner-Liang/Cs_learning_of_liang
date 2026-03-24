/*
【题目】12  区域修改
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

//区域修改，只修改目标区域之上的节点，但是之下的正确性不保证
//查询到绿色节点以下的节点时候，把绿色节点的信息下方
//这种方法叫懒标记

/*给定一个 n 位数组和两种操作:

​ 操作1：数组中某个区间的所有数字加上一个值

​ 操作2：查询数组中某个区间的所有数字之和*/
#include <iostream>
using namespace std;
struct Node
{
	int sum, ag = 0, l, r;
};
void updata22(Node* tree, int ind);
void build_tree22(int* a, Node* tree, int ind, int l, int r);
void add22(Node* tree, int ind,int l,int r, int x, int y,int k);
void down22(Node* tree, int ind);
int query22(Node* tree,int ind, int x, int y);
int main12()
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

	int n, m;
	cin >> n >> m;
	Node tree[4005];
	int a[1005] = { 0 };
	for (int i = 1;i <= n;i++)cin >> a[i];
	build_tree22(a, tree, 1, 1, n);
	for (int i = 0,a,b,c,d;i < m;i++)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c >> d;
			if (b > c)continue;
			add22(tree, 1,1,n, b, c, d);
		}
		else
		{
			cin >> b >> c;
			if (b > c)cout << 0 << endl;
			else cout << query22(tree,1, b, c) << endl;
		}
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void updata22(Node* tree, int ind)
{
	tree[ind].sum = tree[ind * 2].sum + tree[ind * 2 + 1].sum;
	return;
}
void build_tree22(int* a, Node* tree, int ind, int l, int r)
{
	tree[ind].l = l;
	tree[ind].r = r;
	if (l == r)
	{
		tree[ind].sum = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build_tree22(a, tree, ind * 2, l, mid);
	build_tree22(a, tree, ind * 2 + 1, mid + 1, r);
	updata22(tree, ind);
	return;
}
void add22(Node* tree, int ind,int l,int r, int x, int y,int k)
{
	if (x == l && r == y)
	{
		tree[ind].sum += (y - x + 1) * k;
		tree[ind].ag += k;
		return;
	}
	int mid = (l + r) / 2;
	down22(tree, ind);
	if (y <= mid)
	{
		add22(tree, 2 * ind, l, mid, x, y, k);
	}
	else if (x > mid)
	{
		add22(tree, ind * 2 + 1, mid + 1, r, x, y, k);
	}
	else
	{
		add22(tree, ind * 2, l, mid, x, mid, k);
		add22(tree, ind * 2 + 1, mid + 1, r, mid + 1, y, k);
	}
	updata22(tree, ind);
	return;
}
void down22(Node* tree, int ind)
{
	if (tree[ind].ag == 0)return;
	tree[2 * ind].ag += tree[ind].ag;
	tree[ind * 2 + 1].ag += tree[ind].ag;
	tree[ind * 2].sum += (tree[ind * 2].r - tree[ind * 2].l + 1) * tree[ind].ag;
	tree[ind * 2+1].sum += (tree[ind * 2+1].r - tree[ind * 2+1].l + 1) * tree[ind].ag;
	tree[ind].ag = 0;
	return;
}
int query22(Node* tree,int ind, int x, int y)
{
	if (x <= tree[ind].l && y >= tree[ind].r)
	{
		return tree[ind].sum;
	}
	int mid = (tree[ind].l + tree[ind].r) / 2;
	int sum = 0;
	down22(tree, ind);
	if (x <= mid)
	{
		sum += query22(tree, 2 * ind, x, y);
	}
	if (y > mid)
	{
		sum += query22(tree, 2 * ind + 1, x, y);
	}
	return sum;
}