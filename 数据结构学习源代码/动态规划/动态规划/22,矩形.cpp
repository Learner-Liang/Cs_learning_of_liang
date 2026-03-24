#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
//HZOJ 51
int main22()
{
	//dp[i][j]i,j表示坐标表示其合法矩形坐标：左上角：右下角点合法点个数
	//f[i][j]表示iJ向下数的白色格子数量
	//测试
	int n,m;
	cin >> n >> m;
	int dp[1005][1005] = { 0 };
	int f[1005][1005] = { 0 };
	/*int up[1005][1005] = {0}, left[1005][1005] = {0};
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			scanf("%d", &dp[i][j]);
			if (dp[i][j])
			{
				left[i][j] = 1 + left[i][j - 1];
				up[i][j] = 1 + up[i - 1][j];
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1]- dp[i - 1][j - 1];
				int ans = 0;
				int temp = up[i][j];
				for (int x = 0;x < left[i][j];x++)
				{
					if (temp > up[i][j-x])temp = up[i][j-x];
					ans += temp;
				}
				dp[i][j] += ans;
			}
			else
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1]- dp[i - 1][j - 1];
			dp[i][j] %= 100007;
		}
	}
	cout << dp[n][m];*/
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			scanf("%d", &f[i][j]);
		}
	}
	for (int i = n-1;i >=1 ;i--)
	{
		for (int j = 1;j <= m;j++)
		{
			if (f[i][j]) f[i][j] += f[i + 1][j];
		}
	}
	int ans = 0;
	for (int i = 1;i <= n;i++)
	{
		for (int j = m;j >= 1;j--)
		{
			int k = j;
			while (k <= m && f[i][k] >= f[i][j])k++;
			dp[i][j] = f[i][j] * (k - j) + dp[i][k];//由此可以看出，与上一行无关，因而可以改为一位数组
			//求最近小于关系：单调栈
			dp[i][j] %= 100007;
			ans += dp[i][j];
			ans %= 100007;
		}
	}
	cout << ans;

	//优化

	return 0;
}