/*
【题目】19 复合线段树
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
using namespace std;
/*已知一个数列，你需要进行下面三种操作：

将某区间每一个数乘上 x​

将某区间每一个数加上 x

求出某区间每一个数的和*/
int cnt_ = 1;
int p;
struct NODE
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

	int l, r, sum;
	int time=1, tag=0;//两个懒标记
	int cnt;//节点的数量
};
void up__data(NODE* tree, int ind);
void build_tree(int* a, NODE* tree, int ind,int l,int r);
void down_data(NODE* tree, int ind);
int queryk(NODE* tree, int ind, int l, int r,int x,int y);
void modify_time(NODE* tree,int ind, int l, int r, int x, int y, int k);
void modify_add(NODE* tree,int ind, int l, int r, int x, int y, int k);
int main19()
{
	int n,m;
	cin >> n >> m >> p;
	int a[100];
	for (int i = 1;i <= n;i++)  scanf("%d", a + i);
	NODE tree[100];
	build_tree(a, tree, 1, 1, n);
	for (int i = 0, ch, x, y, k;i < m;i++)
	{
		cin >> ch;
		if (ch == 1)
		{
			scanf("%d%d%d", &x, &y, &k);
			modify_time(tree, 1, 1, n, x, y, k);

		}
		else if (ch == 2)
		{
			scanf("%d%d%d", &x, &y, &k);
			modify_add(tree, 1, 1, n, x, y, k);
		}
		else
		{
			scanf("%d%d", &x, &y);
			cout << queryk(tree , 1, 1, n, x, y)%p;
		}
	}

	

// 步骤4（代码实现）：输出结果并返回。
// 目的：给出最终答案并结束程序执行。
// 实现：调用输出语句打印结果，并通过 return 结束流程。
return 0;
}
void up__data(NODE* tree, int ind)
{
	tree[ind].sum = (tree[tree[ind].l].sum + tree[tree[ind].r].sum)%p;
	return;
}
void build_tree(int* a, NODE* tree, int ind,int l,int r)
{
	tree[ind].l = ++cnt_;
	tree[ind].r = ++cnt_;
	tree[ind].cnt = r - l + 1;
	if (l == r)
	{
		tree[ind].sum = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build_tree(a, tree, tree[ind].l, l, mid);
	build_tree(a, tree, tree[ind].r,  mid+1,r);
	up__data(tree, ind);
	return;
}
void down_data(NODE* tree, int ind)
{
	/*if (tree[ind].tag != 0)
	{
		tree[tree[ind].l].tag += tree[ind].tag;
		tree[tree[ind].l].sum += tree[ind].tag * tree[tree[ind].l].cnt;
		tree[tree[ind].r].tag += tree[ind].tag;
		tree[tree[ind].r].sum += tree[ind].tag * tree[tree[ind].r].cnt;
		tree[ind].tag = 0;
	}
	if (tree[ind].time != 1)
	{
		tree[tree[ind].l].time *= tree[ind].time;
		tree[tree[ind].r].time *= tree[ind].time;
		tree[tree[ind].l].sum *= tree[ind].time;
		tree[tree[ind].r].sum *= tree[ind].time;
	}*/
	//此处存在问题，这么更新设计乘法和加法的更新顺序问题，先更新乘法，同时注意，加法并不是单纯相加就可以
	if (tree[ind].time != 1)
	{
		tree[tree[ind].l].time *= tree[ind].time;
		tree[tree[ind].r].time *= tree[ind].time;
		tree[tree[ind].l].tag *= tree[ind].time;
		tree[tree[ind].r].tag *= tree[ind].time;
		tree[tree[ind].l].sum *= tree[ind].time;
		tree[tree[ind].r].sum *=tree[ind].time;
		tree[ind].time = 1;
	}
	if (tree[ind].tag != 0)
	{
		tree[tree[ind].l].tag += tree[ind].tag;
		tree[tree[ind].l].sum += tree[ind].tag * tree[tree[ind].l].cnt;
		tree[tree[ind].r].tag += tree[ind].tag;
		tree[tree[ind].r].sum += tree[ind].tag * tree[tree[ind].r].cnt;
		tree[ind].tag = 0;
	}
	return;
}
int queryk(NODE* tree, int ind, int l, int r,int x, int y)
{
	if (x<=l&&y>=r)
	{
		return tree[ind].sum;
	}
	int mid = (l + r) / 2;
	down_data(tree, ind);
	int ans = 0;
	if (x <= mid)ans += queryk(tree, tree[ind].l, l, mid, x, y);
	if (y > mid)ans += queryk(tree, tree[ind].r, mid + 1, r, x, y);
	return ans%p;

}
void modify_time(NODE* tree,int ind, int l, int r, int x, int y, int k)
{
	if (x <= l && y >= r)
	{
		tree[ind].tag *= k;
		tree[ind].time *= k;
		tree[ind].sum *= k;
		return;
	}
	down_data(tree, ind);
	int mid = (l + r) / 2;
	if (x <= mid)modify_time(tree, tree[ind].l, l, mid, x, y, k);
	if (y > mid)modify_time(tree, tree[ind].r, mid + 1, r, x, y, k);
	up__data(tree, ind);
	return;
}
void modify_add(NODE* tree,int ind, int l, int r, int x, int y, int k)
{
	if (x <= l && y >= r)
	{
		tree[ind].tag += k;
		tree[ind].sum += (r - l + 1) * k;
		return;
	}
	down_data(tree, ind);
	int mid = (l + r) / 2;
	if (x <= mid)modify_add(tree, tree[ind].l, l, mid, x, y, k);
	if (y > mid)modify_add(tree, tree[ind].r, mid + 1, r, x, y, k);
	up__data(tree, ind);
	return;
}