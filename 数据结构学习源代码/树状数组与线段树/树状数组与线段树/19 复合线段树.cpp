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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

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
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> m >> p;
	int a[100];
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
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
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			cout << queryk(tree , 1, 1, n, x, y)%p;
		}
	}

	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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
		// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
		// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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