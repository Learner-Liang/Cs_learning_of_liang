//没有明确的根节点，假设一个根节点
// notepad
//解题思路：有的题目看成树会很好接解决
#define _CRT_SECURE_NO_WARNINGS
/*在 W 星球上有 n 个国家。为了各自国家的经济发展，他们决定在各个国家之间建设双向道路使得国家之间连通。但是每个国家的国王都很吝啬，
他们只愿意修建恰好 n−1 条双向道路。
每条道路的修建都要付出一定的费用，这个费用等于道路长度乘以道路两端 的国家个数之差的绝对值。例如，在下图中，
虚线所示道路两端分别有 2 个、4 个国家，如果该道路长度为 1，则费用为 1×∣2−4∣=2。图中圆圈里的数字表示国家的编号。*/
#include <iostream>
using namespace std;
struct edge
{
	int first = 0, second = 0;
	int price=0;
};
int cnt_ = 0;
int n;
int nums[100] = { 0 };
void add__(edge* edge, int* head, int a, int b,int price)
{
	edge[++cnt_] = { b,head[a],price };
	head[a] = cnt_;
	return;
}
int ans899 = 0;
void dfs1(int* head, edge* edge, int f, int s)
{
	nums[s] = 1;
	int p = head[s];
	while (p)
	{
		int to = edge[p].first;
		if (to != f)
		{
			dfs1(head, edge, s, to);
			nums[s] += nums[to];
			ans899 += edge[p].price * abs(n - nums[to] * 2);
		}
		p = edge[p].second;
	}
}
int getprice(edge* edge, int* head, int root)//错误，必须要父节点防止出现无限递归问题
{
	int sum = 0;
	int p = head[root];
	while (p)
	{
		int to = edge[p].first;
		if (to != root)
		{
			cout << sum;
			sum += (edge[p].price) * abs(n - nums[to]*2);
		    sum +=getprice(edge, head, to);
		}
		p = edge[p].second;
	}
	return sum;
}
int main5()
{
	cin >> n;
	int head[100] = { 0 };
	edge Edge[200] = { 0 };
	for (int i = 1,a,b,c;i < n;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		add__(Edge, head, a, b, c);
		add__(Edge, head, b, a, c);
	}
	dfs1(head,Edge,0, 1);
	//getprice(Edge, head, 1);
	cout << ans899;
	//cout << getprice(Edge,head,1);
	return 0;
}