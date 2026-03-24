#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main9()
{
	//HZOJ 47
	//给一个能承重V的背包，和n件物品，我们用重量和价值的二元组来表示一个物品，第i件物品表示为（Vi，Wi），问：在背包不超重的情况下，得到物品的最大价值是多少？
	int v, n;
	cin >> v >> n;
	//dp[i][j]i件物品，承重为j时候，获得的最大价值
	//分为是否选第i件物品
	//d[i][j]=max(d[i-1][j],d[i-1][j-w[i]]+val[i])
	


	//方法1
	/*int dp[105][10005] = {0};
	int v[105] = { 0 }, w[105] = { 0 };//重量与价值
	for (int i = 1;i <= n;i++)
		scanf_s("%d%d", v + i, w + i);
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= v;j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (j - w[i] <= 0)continue;
			dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]);
		}
	}

	//方法2：滚动数组:节约内存
	for (int i = 1,v,w;i <= n;i++)
	{
		cin >> v>>w;//可以边处理，边读入
		for (int j = 1;j <= v;j++)
		{
			int ind = i % 2, rind = (i - 1) % 2;
			dp[ind][j] = dp[rind][j];
	      if (j - w <= 0)continue;
			dp[ind][j] = max(dp[rind][j], dp[rind][j - v] + w);
		}
	}
	printf("%d", dp[n % 2][v]);*/
	return 0;
}