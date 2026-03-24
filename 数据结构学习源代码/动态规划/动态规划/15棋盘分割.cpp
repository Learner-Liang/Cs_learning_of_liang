#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int main15()
{
	//dp[n][i][j][k][l]
	int n;
	cin >> n;
	int val[10][10] = { 0 };
	//val表示大矩阵的所有元素之和
	//二维前缀和数组
	for (int i = 1;i <= 8;i++)
	{
		for (int j = 1;j <= 8;j++)
		{
			cin >> val[i][j];
			val[i][j] += val[i - 1][j] + val[i][j - 1] - val[i - 1][j - 1];
		}
	}

	int dp[18][10][10][10][10] = { 0 };
	for (int i = 1;i <= 8;i++)
	{
		for (int j = 1;j <= 8;j++)
		{
			for (int k = i;k <= 8;k++)
			{
				for (int l = j;l <= 8;l++)
				{
					int g = (val[k][l] - val[k][j - 1] - val[i - 1][l] + val[i - 1][j - 1]);
					dp[1][i][j][k][l] = g * g;
				}
			}
		}
	}
	for (int t = 2;t<= n;t++)
	{
		for (int i = 1;i <= 8;i++)
		{
			for (int j = 1;j <= 8;j++)
			{
				for (int k = i;k <= 8;k++)
				{
					for (int l = j;l <= 8;l++)
					{
						dp[t][i][j][k][l] = 0x3f3f3f3f;
						for (int l1 = i;l1 < k;l1++)
						{
							//存在问题部分：有一个部分继续分
							dp[t][i][j][k][l] = min(dp[1][i][j][l1][l] + dp[t - 1][l1+1][j][k][l],dp[t][i][j][k][l]);
						}
						for (int l2 = j;l2 < l;l2++)
						{
							dp[t][i][j][k][l] = min(dp[1][i][j][k][l2] + dp[t - 1][i][l2+1][k][l], dp[t][i][j][k][l]);
						} 
					}
				}
			}
		}
	}
	cout << dp[n][1][1][8][8]; 
	return 0;
}