#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main10()
{
	/*有N种物品和一个容量为 V 的背包，每种物品都有无限件可用。

	第 i 种物品的体积是Ci，价值是Wi。求解在不超过背包容量的情况下，能够获得的最大价值。*/
		//dp[i][j]i件物品，承重为j时候，获得的最大价值
		//分为是否选第i件物品
		//d[i][j]=max(d[i-1][j],d[i-1][j-w[i]*n]+val[i]*n)
	int N, V;
	cin >> N >> V;
	int dp[10005][10005] = { 0 };
	int v[10005] = { 0 }, w[10005] = { 0 };
	for (int i = 1;i <= N;i++)
		scanf_s("%d%d", v + i, w + i);
	for (int i = 1;i <= N;i++)
	{
		for (int j = 1;j <= V;j++)
		{
			dp[i][j] = dp[i - 1][j];
			int n = 1;
			while (j - n * v[i] >= 0)
				dp[i][j] = max(dp[i][j], dp[i - 1][j - n * v[i]] + w[i] * n);
		}
	}
	

	//for (int i = 1,c,v;i <= N;i++)
	//{
	//	cin >> c >> v;
	//	for (int j = c;j <= V;j++)//此处无需倒置
	//	{
	//		dp[j] = max(dp[j], dp[j - c] + v);
	//	}
	//}
	return 0;
}