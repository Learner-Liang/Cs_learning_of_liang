#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//开辟两个数组
//第一个数组第一位不使用，每一位存储一条边:第一个数字存储指向的点，第二个数字存储下一个子节点所在当前数字中的编号
//head数组：存储每一条边最后一个节点数组下标
int cnt___ = 0;
struct list_edge
{
	int first=0, second=0;
};
void add___(list_edge* edge,int*head,int a, int b)
{
	edge[++cnt___] = { b,head[a] };
	head[a] = cnt___;
	return;
}
void output___(list_edge* edge, int* head, int a)
{
	cout << a << ":";
	int p = head[a];
	while (p)
	{
		cout << edge[p].first<<" ";
		p = edge[p].second;
	}
	cout << endl;
}
int main3()
{
	int n, m;//点和边的数量
	cin >> n >> m;
	list_edge edge[100] = { 0 };
	int head[100] = { 0 };
	for (int i = 0, a, b;i < m;i++)//a，b表示出发点和到达点
	{
		cin >> a >> b;
		add___(edge,head,a, b);
	}
	for (int i = 1;i <= n;i++)
	{
		output___(edge, head, i);
	}
	return 0;
}