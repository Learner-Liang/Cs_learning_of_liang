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
	cin >> n >> m;
	int a[100] = { 0 };
	Node_ tree[100] = { 0 };
	int ind[100] = { 0 };//记录每个根节点的编号
	ind[0] = 1;
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
void modify_(Node_* tree,int ind,int ind_,int l,int r, int a, int b)//ind是历史树的编号
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
//	return 0;
//}
