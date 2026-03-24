//优化方法
// 去除冗余状态
//
//
//p1541
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int main16() 
{
	int n, m;
	cin >> n >> m;
	//dp[a][b][c][d]
	int N[400] = { 0 };
	for (int i = 1;i <= n;i++)
		scanf_s("%d", N + i);
	int num[5] = { 0 };
	for (int i = 1,a;i <= m;i++)
	{
		scanf_s("%d", &a);
		num[a]++;
	}

	int dp[124][124][124][124] = { 0 };
	dp[0][0][0][0] = N[1];
	for (int i = 0;i <= num[1];i++)
	{
		for (int j = 0;j <= num[2];j++)
		{
			for (int k = 0;k <= num[3];k++)
			{
				for (int l = 0;l <= num[4];l++)
				{
					int s = i + 2 * j + 3 * k + 4 * l + 1;
					if (i)
						dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l]);
					if(j)
						dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j-1][k][l]);
					if(k)
						dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k-1][l]);
					if(l)
						dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l-1]);
					dp[i][j][k][l] += N[s];
				}
			}
		}
	}
	//去除冗余状态：滚动数组：优化空间复杂度
	//存储的状态只有a-1与a两种，第一种是a-1其余是a，可以直接改为三维数组
	printf("%d", dp[num[1]][num[2]][num[3]][num[4]]);
	return 0;
}