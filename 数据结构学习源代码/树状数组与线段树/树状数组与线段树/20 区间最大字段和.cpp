/*
【题目】20 区间最大字段和
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

/*​ 给定长度为N的数列A，以及M条指令 (N≤500000, M≤100000)，每条指令可能是以下两种之一：

​ “2 x y”，把 A[x] 改成 y。

// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

​ “1 x y”，查询区间 [x,y] 中的最大连续子段和，即max(x≤l≤r≤y)∑ri=l
A[i]。*/
//一个节点中维护三个最值，就是左节点中最大值和以左节点区间最后一位向前的最大值，还有右
//右区间维护最左的一个点
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MID int mid=(l+r)>>1
int _cnt_ = 2, t1 = 0, t2 = 1, flag = 1;//注意，树的遍历区间是从左逐步到右，up更新操作类似与区间合并
//如果是第一个节点，直接赋值给t1即可，如不是，则向上更新
struct node
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

	int l, r, sum;
	int m, lm, rm;
};
void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return;
}
void query_max(node* tree, int ind, int l, int r, int x, int y);
void build_tree_max(int* a, node* tree, int ind, int l, int r);
void updata_max(node* tree,int a, int b, int c);
void modify_max(node* tree, int ind,int l, int r, int x, int y);
int main20()
{
	int n, m;
	scanf("%d%d", &n, &m);
	int num[100] = { 0 };
	node tree[100];
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 1;i <= n;i++)scanf("%d", num + i);
	build_tree_max(num, tree, 2,  1, n);
	for (int i = 1,k,x,y;i <= m;i++)
	{
		scanf("%d%d%d", &k, &x, &y);
		if (k == 1)
		{
			if (x > y)swap(x, y);
			flag = 1;
			query_max(tree, 2, 1, n, x, y);
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			cout << tree[t2].m << endl;
		}
		else
		{
			modify_max(tree, 2, 1, n, x, y);
		}
	}
	return 0;
}
void query_max(node* tree, int ind, int l, int r, int x, int y)
{
	if (x <= l && y >= r)
	{
		if (flag)
		{
			tree[t1] = tree[ind];
			flag = 0;
		}
		else
		{
			updata_max(tree, t1, t2, ind);
		}
		swap(t1, t2);
		return;
	}
	MID;
	if(x<=mid)query_max(tree, tree[ind].l, l, mid, x, y);
	if(y>mid)query_max(tree, tree[ind].r, mid + 1, r, x, y);

	return;
}
void build_tree_max(int* a, node* tree, int ind, int l, int r)
{
	tree[ind].l = ++_cnt_;
	tree[ind].r = ++_cnt_;
	if (l == r)
	{
		tree[ind].sum = tree[ind].lm = tree[ind].rm = tree[ind].m=a[l];
		return;
	}
	MID;
	build_tree_max(a, tree, tree[ind].l, l, mid);
	build_tree_max(a, tree, tree[ind].r, mid + 1, r);
	updata_max(tree,ind, tree[ind].l, tree[ind].r);
	return;
}
void updata_max(node* tree,int a, int b, int c)
{
	tree[a].sum = tree[b].sum + tree[c].sum;
	tree[a].lm = max(tree[b].lm, tree[b].sum + tree[c].lm);
	tree[a].rm = max(tree[c].rm, tree[c].sum + tree[b].rm);
	tree[a].m = max(tree[b].m, tree[c].m);
	tree[a].m = max(tree[a].m, tree[b].rm+ tree[c].lm);
	return;
}
void modify_max(node* tree,int ind, int l, int r, int x, int y)
{
	if (l == r)
	{
		tree[ind].sum = tree[ind].m = tree[l].lm = tree[l].rm = y;
		//cout << l<<"xiugai"<<tree[ind].m << endl;
		return;
	}
	MID;
	if (x <= mid)modify_max(tree, tree[ind].l, l, mid, x, y);
	else modify_max(tree,tree[ind].r, mid + 1,r, x, y);
	updata_max(tree,ind, tree[ind].l, tree[ind].r);
	return;
}