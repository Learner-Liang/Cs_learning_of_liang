#include <iostream>
using namespace std;
/*给定一棵 n 个结点的树，树没有边权。请求出树的直径是多少，即树上的最长路径长度是多少。*/
//根节点的值不确定
//同时考虑子节点与父节的转移关系之外，还要考虑跨越父节点的转移关系


//dp[x]=max(dp[xson]+1)
//\ans=max(ans,dp[x1]+dp[x2+2])
//dp[x]代表以x为端点，向下的最长路径长度
int count1 = 0;
struct EDGE
{
	int son_val, son;
};
int max_ans = 0;
void _add_(int* head, EDGE* edge, int a, int b)
{
	edge[++(count1)] = { b,head[a] };
	head[a] = count1;
	return;
}
void get_jump_dp(int* head, EDGE* edge, int* dp, int f,int s)
{
	int x1 = -1, x2 = -1;//若是没有节点，就会导致为2，即默认值是2，通过赋值为-1，可以将默认值改为0
	for (int p = head[s];p;p = edge[p].son)
	{
		int to = edge[p].son_val;
		if (to == f)continue;
		get_jump_dp(head, edge ,dp, s, to);
		dp[s] = max(dp[s], dp[to]+1);
		if (dp[to] > x1)x2 = x1, x1 = dp[to];
		else if (dp[to] > x2)x2 = dp[to];
	}
	max_ans = max(max_ans,x1+x2+ 2);
	return;
}
int main8()
{
	int n;
	cin >> n;
	int head[100] = { 0 };
	EDGE edge[100] = { 0 };
	int dp[100] = { 0 };
	for (int i = 1,a,b;i < n;i++)
	{
		cin >> a >> b;
		_add_(head, edge, a, b);
		_add_(head, edge, b, a);

	}
	//for (int i = 1;i <= n;i++)cout << head[i] << endl;
	get_jump_dp(head, edge,dp,0,1);
	cout << max_ans;
	return 0;
}