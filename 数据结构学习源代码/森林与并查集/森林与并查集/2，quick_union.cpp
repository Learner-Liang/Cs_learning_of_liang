// quick_union
// 所有子节点都是直接或者间接指向根节点，此树不是父节点指向子节点，而是子节点指向父节点
//合并操作本质上是将一棵树作为另一棵树的子树
//改变父节点指向的下表，一开始值都为自己的下表值，之后将自己的值修改为子节点下标值
//根节点的父节点是自己，因而，值为自己的下标
#include <iostream>
using namespace std;
#define max 10005
int color[max] = { 0 };
int size[max + 5];//每个节点的节点数量，起始为1
void init(int);
int find(int n);//返回根节点下标
int merge(int a, int b);
void output(int n);
void output_line(int i);
//并查集的按秩优化：按照树高和节点数量
//路径压缩优化：所有的节点挂在根节点下面，
//在find操作中完成，在查询过程中把所有根节点挂上去，和quick_find操作类似
int main()
{
	int n, a, b;
	cin >> n;
	init(n);
	while (scanf_s("%d %d", &a, &b))
	{
		if (merge(a, b))
			printf("merge %d with %d.\n", a, b);
		output(n);
	}
	return 0;
}
void init(int n)
{
	for (int i = 0;i < n;i++)
	{
		color[i] = i;
		size[i] = 1;
	}
	return ;
}
int find(int n)
{
	if (color[n] == n)return n;
	return find(color[n]);
}
int merge(int a, int b)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return 0;
	color[bb] = aa;
	return 1;
}
void output(int n)
{
	for (int i = 0;i < n;i++)
	{
		output_line(i);
	}
}
void output_line(int i)
{
	while (color[i] != i)
	{
		printf("(%3d:%d)->", i, color[i]);
		i = color[i];
	}
	printf("(%3d:%d)\n", i, i);
}
//按秩优化
int size[max + 5];//每个节点的节点数量，起始为1
int merge1(int a, int b)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return 0;
	//节点数量多的当爹
	if (size[a] > size[b])
	{
		size[aa] += size[bb];
		color[bb] = aa;
	}
	else {
		size[bb] += size[a];
		color[aa] = bb;
	}
	return 1;
}
//路径压缩优化
int find1(int n)
{
	if (color[n] == n)return n;
	color[n] = find(color[n]);
	return color[n];
}