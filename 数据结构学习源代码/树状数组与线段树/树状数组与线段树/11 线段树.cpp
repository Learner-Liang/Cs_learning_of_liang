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
	tree[ind] = max(tree[ind * 2], tree[ind * 2 + 1]);
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