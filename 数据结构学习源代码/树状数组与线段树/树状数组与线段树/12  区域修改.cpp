//区域修改，只修改目标区域之上的节点，但是之下的正确性不保证
//查询到绿色节点以下的节点时候，把绿色节点的信息下方
//这种方法叫懒标记

/*给定一个 n 位数组和两种操作:

​ 操作1：数组中某个区间的所有数字加上一个值

​ 操作2：查询数组中某个区间的所有数字之和*/
#include <iostream>
using namespace std;
struct Node
{
	int sum, ag = 0, l, r;
};
void updata22(Node* tree, int ind);
void build_tree22(int* a, Node* tree, int ind, int l, int r);
void add22(Node* tree, int ind,int l,int r, int x, int y,int k);
void down22(Node* tree, int ind);
int query22(Node* tree,int ind, int x, int y);
int main12()
{
	int n, m;
	cin >> n >> m;
	Node tree[4005];
	int a[1005] = { 0 };
	for (int i = 1;i <= n;i++)cin >> a[i];
	build_tree22(a, tree, 1, 1, n);
	for (int i = 0,a,b,c,d;i < m;i++)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c >> d;
			if (b > c)continue;
			add22(tree, 1,1,n, b, c, d);
		}
		else
		{
			cin >> b >> c;
			if (b > c)cout << 0 << endl;
			else cout << query22(tree,1, b, c) << endl;
		}
	}
	return 0;
}
void updata22(Node* tree, int ind)
{
	tree[ind].sum = tree[ind * 2].sum + tree[ind * 2 + 1].sum;
	return;
}
void build_tree22(int* a, Node* tree, int ind, int l, int r)
{
	tree[ind].l = l;
	tree[ind].r = r;
	if (l == r)
	{
		tree[ind].sum = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build_tree22(a, tree, ind * 2, l, mid);
	build_tree22(a, tree, ind * 2 + 1, mid + 1, r);
	updata22(tree, ind);
	return;
}
void add22(Node* tree, int ind,int l,int r, int x, int y,int k)
{
	if (x == l && r == y)
	{
		tree[ind].sum += (y - x + 1) * k;
		tree[ind].ag += k;
		return;
	}
	int mid = (l + r) / 2;
	down22(tree, ind);
	if (y <= mid)
	{
		add22(tree, 2 * ind, l, mid, x, y, k);
	}
	else if (x > mid)
	{
		add22(tree, ind * 2 + 1, mid + 1, r, x, y, k);
	}
	else
	{
		add22(tree, ind * 2, l, mid, x, mid, k);
		add22(tree, ind * 2 + 1, mid + 1, r, mid + 1, y, k);
	}
	updata22(tree, ind);
	return;
}
void down22(Node* tree, int ind)
{
	if (tree[ind].ag == 0)return;
	tree[2 * ind].ag += tree[ind].ag;
	tree[ind * 2 + 1].ag += tree[ind].ag;
	tree[ind * 2].sum += (tree[ind * 2].r - tree[ind * 2].l + 1) * tree[ind].ag;
	tree[ind * 2+1].sum += (tree[ind * 2+1].r - tree[ind * 2+1].l + 1) * tree[ind].ag;
	tree[ind].ag = 0;
	return;
}
int query22(Node* tree,int ind, int x, int y)
{
	if (x <= tree[ind].l && y >= tree[ind].r)
	{
		return tree[ind].sum;
	}
	int mid = (tree[ind].l + tree[ind].r) / 2;
	int sum = 0;
	down22(tree, ind);
	if (x <= mid)
	{
		sum += query22(tree, 2 * ind, x, y);
	}
	if (y > mid)
	{
		sum += query22(tree, 2 * ind + 1, x, y);
	}
	return sum;
}