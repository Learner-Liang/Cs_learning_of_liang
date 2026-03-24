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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
}
void build_tree11(int* tree, int* num, int ind, int l, int r)
{
	if (l == r)
	{
		tree[ind] = num[l];
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
	cin >> n >> m;
	int max_ = -100000;
	int ind = 0;
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
			if (b > c)cout << -2147483648 << endl;
			else cout << query11(tree, 1, 1, n,b,c)<< endl;
		}
	}
	return 0;
}