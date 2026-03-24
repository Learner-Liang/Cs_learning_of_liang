/*
【题目】14 可持久化线段树
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
struct Node_
{
	int val, l, r;
};
int cnt_tree = 1;
int root = 0;
void build_tree_(int* a ,Node_* tree, int ind, int l, int r);
void updata_(Node_* tree,int ind);
void modify_(Node_* tree, int ind,int ind_,int l,int r, int a, int b);
int query_(Node_* tree, int ind, int c,int l,int n);
int main14()
{
	int n,m;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> m;
	int a[100] = { 0 };
	Node_ tree[100] = { 0 };
	int ind[100] = { 0 };//¼ÿڵı
	ind[0] = 1;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 1;i <= n;i++)scanf("%d", a + i);
	build_tree_(a, tree, 1, 1, n);
	for (int i = 0,a,b,c,d;i < m;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		if (b == 1)
		{
			scanf("%d", &d);
			ind[++root] = ++cnt_tree;
			modify_(tree, ind[a],ind[root],1, n, c,d);
		}
		else
		{
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			cout << query_(tree, ind[a], c,1,n) << endl;
			ind[++root] = ind[a];
		}
	}
	return 0;
}
void build_tree_(int* a ,Node_* tree, int ind, int l, int r)
{
	tree[ind].l = ++cnt_tree;
	tree[ind].r = ++cnt_tree;
	if (l == r)
	{
		tree[ind].val = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build_tree_(a, tree, tree[ind].l, l, mid);
	build_tree_(a, tree, tree[ind].r, mid + 1, r);
	updata_(tree, ind);
	return;
}
void updata_(Node_* tree, int ind)
{
	tree[ind].val = tree[tree[ind].l].val + tree[tree[ind].r].val;
	return;
}
void modify_(Node_* tree,int ind,int ind_,int l,int r, int a, int b)//indʷı
{
	if (r == l)
	{
		tree[ind_].l = tree[ind_].r = ++cnt_tree;
		tree[ind_].val = b;
		return;
	}
	int mid = (l+r) / 2;
	if (a <= mid)
	{
		tree[ind_].r = tree[ind].r;
		tree[ind_].l = ++cnt_tree;
		modify_(tree, tree[ind].l, tree[ind_].l, l, mid, a, b);
	}
	else
	{
		tree[ind_].l = tree[ind].l;
		tree[ind_].r = ++cnt_tree;
		modify_(tree, tree[ind].r, tree[ind_].r, mid + 1, r, a, b);
	}
	updata_(tree, ind_);
	return;
}
int query_(Node_* tree, int ind, int c,int l,int r)
{
	if (l == r)return tree[ind].val;
	int mid = (l + r) / 2;
	if (c <= mid)return query_(tree, tree[ind].l, c, l, mid);
	else return query_(tree, tree[ind].r, c, mid + 1, r);
}
//#include <iostream>
//using namespace std;
//
//struct Node {
//	int c, l, r;
//} tree[30000005];
//int node_cnt = 0, root[1000005];
//int n, m;
//int a[1000005];
//
//int clone(int ind) {
//	++node_cnt;
//	tree[node_cnt] = tree[ind];
//	return node_cnt;
//}
//
//int build_tree(int l, int r) {
//	int ind = ++node_cnt;
//	if (l == r) {
//		tree[ind].c = a[l];
//		return ind;
//	}
//	int mid = (l + r) / 2;
//	tree[ind].l = build_tree(l, mid);
//	tree[ind].r = build_tree(mid + 1, r);
//	return ind;
//}
//
//int modify(int ind, int l, int r, int x, int y) {
//	ind = clone(ind);
//	if (l == r) {
//		tree[ind].c = y;
//		return ind;
//	}
//	int mid = (l + r) / 2;
//	if (x <= mid) tree[ind].l = modify(tree[ind].l, l, mid, x, y);
//	else tree[ind].r = modify(tree[ind].r, mid + 1, r, x, y);
//	return ind;
//}
//
//int query(int ind, int l, int r, int x) {
//	if (l == r) {
//		return tree[ind].c;
//	}
//	int mid = (l + r) / 2;
//	if (x <= mid) return query(tree[ind].l, l, mid, x);
//	return query(tree[ind].r, mid + 1, r, x);
//}
//
//int main() {
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

//	scanf("%d%d", &n, &m);
//	for (int i = 1; i <= n; i++) scanf("%d", a + i);
//	root[0] = build_tree(1, n);
//	for (int i = 1, v, a, b, c; i <= m; i++) {
//		scanf("%d%d%d", &v, &a, &b);
//		if (a == 1) {
//			scanf("%d", &c);
//			root[i] = modify(root[v], 1, n, b, c);
//		}
//		else {
//			cout << query(root[v], 1, n, b) << endl;
//			root[i] = root[v];
//		}
//	}
//	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
//}
