#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main17()
{
	int n, m;
	cin >> n >> m;
	//dp[i][j]i个鸡蛋J层楼，j表示楼数
	//先选从k楼扔，碎了测接下来k-1东楼，没碎的化测试j-k 层楼
	/*int dp[35][1000005] = { 0 };
	for (int i = 1;i <= m;i++)
		dp[1][i] = i;
	for (int i = 2;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			dp[i][j] = j;
			for (int k = 1;k <= j;k++)
			{
		     dp[i][j] = min(dp[i][j], max(dp[i - 1][k - 1], dp[i][j - k])+1);
			}
		}
	}
	cout << dp[n][m];*/



	//最少次数k与j正相关，将k和j互换位置
	//dp[i][j] = k;
	//dp[i][k]=j;  i个鸡蛋，测试k次，最多能测几层楼
	//dp[i][k]=dp[i-1][k-1]+1+dp[i][k-1]
	return 0;
}