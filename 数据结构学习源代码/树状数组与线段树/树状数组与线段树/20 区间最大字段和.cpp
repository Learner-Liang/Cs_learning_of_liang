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
	int l, r, sum;
	int m, lm, rm;
};
void swap(int& x, int& y)
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

	int temp = x;
	x = y;
	y = temp;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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