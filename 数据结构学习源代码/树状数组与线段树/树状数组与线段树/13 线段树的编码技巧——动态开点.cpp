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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

	int c, l, r;
};
int node_cnt = 1;
void build_tree(Node* tree,int* a, int ind, int l, int r);
void updata(Node* tree, int ind);
void modify(Node* tree, int ind,int l,int r, int b, int c);
int query(Node* tree, int ind,int l, int r, int x, int y);
int main13()
{
	Node tree[100];//2n个节点
	int a[100];
	int n, m;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> m;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
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
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			if (b <= c)cout << query(tree,1,1,n,b,c) << endl;
		}
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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
	
	// 步骤3细化（更新语句解释）：这里执行状态更新（如 max/min/松弛）。
	// 数学含义：用“当前候选值”与“历史最优值”比较，保证不丢失最优解。
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