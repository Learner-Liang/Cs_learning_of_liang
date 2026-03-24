//为了使用完全二叉树，会开辟4*n-1个节点，但是实际上只要2n个
#include <iostream>
using namespace std;
//用模板1演示
//​ 操作1：修改数组中某个位置的值
//
//​ 操作2：查询数组中某个区间的最大值
struct Node
{
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
	cin >> n >> m;
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
			if (b <= c)cout << query(tree,1,1,n,b,c) << endl;
		}
	}
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