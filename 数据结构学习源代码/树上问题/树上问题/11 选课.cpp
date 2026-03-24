#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
using namespace std;
vector<int>g[305];
int valk[305] = { 0 };
int countt[305] = { 0 };
void GETDP(int (*dp)[305],int m,int fa,int son);
int main10()
{
	int n, m;
	cin >> n >> m;
	int dp[305][305] = { 0 };
	for (int i = 1,a,b;i <= n;i++)
	{
		scanf("%d%d", &a, &b);
		valk[i] = b;
		g[a].push_back(i);
	}
	m += 1;
	GETDP(dp, m, -1, 0);
	cout << dp[0][m];
	return 0;
}
void GETDP(int (*dp)[305],int m,int fa,int son)
{
	countt[son] = 1;
	//dp[son][0] = 0;
	dp[son][1] = valk[son];
	int n = g[son].size();
	for (int i = 0;i < n;i++)
	{
		GETDP(dp, m, son, g[son][i]);
		countt[son] += countt[g[son][i]];
		for (int j = min(m, countt[son]);j>=2;j--)
		{
			int s = j - 1;
			for (int k = 1;k <= countt[g[son][i]];k++)
			{
				if (k > s)break;
				dp[son][j] = max(dp[son][j], dp[son][j - k] + dp[g[son][i]][k]);
			}
		}
	}
	return;

}