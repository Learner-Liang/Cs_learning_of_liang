//p1509
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
int main29()
{
	int dp[105][105] = { 0 }, Min_time[105][105] = { 0 };
	int rmb[104] = { 0 }, rp[104] = { 0 }, time[104] = { 0 };
	int n, m, r;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d%d%d", rmb + i, rp + i, time + i);
	}
	cin >> m >> r;
	for (int i = 1;i <= n;i++)
	{
		for (int x = m;m >= rmb[i];x--)
		{
			for (int y = r;y >= rp[i];y--)
			{
				if (dp[x][y] < dp[x - rmb[i]][y - rp[i]] + 1)
				{
					dp[x][y] = dp[x - rmb[i]][y - rp[i]] + 1;
					Min_time[x][y] = Min_time[x - rmb[i]][y - rp[i]] + time[i];
				}
				else if (dp[x][y] == dp[x - rmb[i]][y - rp[i]] + 1)
				{
					Min_time[x][y] = min(Min_time[x][y], Min_time[x - rmb[i]][y - rp[i]] + time[i]);
				}
			}
		}
	}
	cout << Min_time[m][n];
	return 0;
}