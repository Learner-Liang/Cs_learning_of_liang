/*
【题目】11 线段树
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

//单点修改
//区域查询
//区域修改：懒标记
//科持久化线段树
//假设有n个叶子节点，则空间应当开到4n-1
//给定一个 n 位数组和两种操作 :
//
//​ 操作1：修改数组中某个位置的值
//
//​ 操作2：查询数组中某个区间的最大值
// 采用完全二叉树：父节点下标位i，左节点=2*i 右节点=2*i+
//线段树的模板不一定是完全按照范围·值的这种类型，还可以按照个人需求加入一些东西，如此题中的区间最大值


//总结：
//完全二叉树:因而不需要记录和的范围，就是区间，自带此信息
//区间
//向上更新：用来两个子节点更新本节点的值
//下沉标记：将本节点的懒惰标记更新给两个子节点


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
void updata11(int* tree, int ind)
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

	
	// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
	// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。
	tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);
}
void build_tree11(int* tree, int* num, int ind, int l, int r)
{
	if (l == r)
	{
		tree[ind] = num[l];
		

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return;
	}
	int mid = (l + r) / 2;
	build_tree11(tree, num, 2 * ind, l, mid);
	build_tree11(tree, num, 2 * ind + 1, mid + 1, r);
	updata11(tree, ind);
}
void modify11(int* tree, int ind, int l, int r,int b, int c)
{
	if (l == r)
	{
		tree[ind] = c;
		return;
	}
	int mid = (l + r) / 2;
	if (b <= mid)modify11(tree, 2 * ind, l, mid, b, c);
	else modify11(tree, ind * 2 + 1, mid + 1, r, b, c);
	updata11(tree, ind);
	//tree[ind]=max(c,tree[ind]),这是错误的，因为tree[ind]中最大值可能就是被改变的值
	return;
}
int query11(int* tree,int ind,int l,int r, int b, int c)
{
	if (b <= l && c >= r)return tree[ind];
	int mid = (l + r) / 2;
	if (c <= mid)return query11(tree, 2 * ind, l, mid, b, c);
	else if (b > mid)return query11(tree, ind * 2 + 1, mid + 1, r, b, c);
	else return max(query11(tree, 2 * ind, l, mid, b, mid), query11(tree, 2 * ind + 1, mid + 1, r, mid + 1, c));
	/*ng long ans=-219393939;
	if(b<=mid)ans=max(ans,query(tree,2*ind,l,mid,b,c));
	if(c>mid) ans=max(ans,query(tree,2*ind+1,mid+1,r,b,c));
	return ans;*/
}
		
int main11()
{
	int n, m;
	int num[100], tree[100] = { 0 };
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> n >> m;
	int max_ = -100000;
	int ind = 0;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 1;i <= n;i++)scanf("%d", num + i);
	build_tree11(tree, num, 1, 1, n);
	for (int i = 1, a, b, c;i <= m;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1)
		{
			if (b > c)continue;
			num[b] = c;
			modify11(tree,1,1, n, b, c);
		}
		else
		{
			
			// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
			if (b > c)cout << -2147483648 << endl;
			else cout << query11(tree, 1, 1, n,b,c)<< endl;
		}
	}
	return 0;
}