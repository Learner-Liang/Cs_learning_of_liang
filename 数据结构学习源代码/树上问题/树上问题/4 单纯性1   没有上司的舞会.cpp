#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
/*​ Ural大学有N名职员，编号为1∼N。他们的关系就像一棵以校长为根的树，
父节点就是子节点的直接上司。每个职员有一个快乐指数，用整数 Hi 给出，其中 1≤i≤N。现在要召开一场周年庆宴会，
不过，没有职员愿意和直接上司一起参会。在满足这个条件的前提下，主办方希望邀请一部分职员参会，
使得所有参会职员的快乐指数总和最大，求这个最大值。
*/


//上司就是父节点
//单纯型：只要考虑子节点和父节点的转移关系
//状态定义  确定转移方程  
//dp[x][0]  dp[x][1]代表x参加与不参加的最大值
//dp[x][0]=所有子节点去或者不去的最大值的和值
//dp[x][1]=所有子节点不去的和值
struct edge
{
	int first = 0, second = 0;
};
int cnt__ = 0;
int h[6005] = { 0 };
void add__(edge* edge, int* head, int a, int b)
{
	edge[++cnt__] = { b,head[a] };
	head[a] = cnt__;
	return;
}
void GetDp_(int (*dp)[2], edge* Edge, int* head, int ind)
{
	dp[ind][0] = 0;
	dp[ind][1] = h[ind];
	int p = head[ind];
	while (p)
	{
		int to = Edge[p].first;
		GetDp_(dp, Edge, head, to);
		dp[ind][0] += max(dp[to][0], dp[to][1]);
		dp[ind][1] += dp[to][0];
		p = Edge[p].second;
	}
	return;
}
int main4()
{
	int n;
	cin >> n;
	int head[6005] = { 0 };
	int fa[6005] = { 0 };//父节点存在的判断
	int dp[6005][2] = { 0 };
	edge Edge[6005] = { 0 };
	for (int i = 1;i <= n;i++) scanf("%d", h + i);
	for (int i = 1,a,b;i < n;i++)
	{
		cin >> a >> b;
		add__(Edge,head,b, a);
		fa[a] = 1;
	}
	int root;
	for (int i = 1;i <= n;i++)
	{
		if (fa[i])continue;
		root = i;
		break;
	}
	GetDp_(dp, Edge, head, root);
	cout << max(dp[root][0], dp[root][1]);
	return 0;
}