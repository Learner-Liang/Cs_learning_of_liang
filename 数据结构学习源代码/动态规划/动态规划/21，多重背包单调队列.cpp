#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
int main21()
{
	int N, V;
	cin >> N >> V;
	int dp[105][10005] = { 0 };
	for (int i = 1, w, v, s;i <= N;i++)
	{
		scanf("%d%d%d", &w, &v, &s);
		//按照余数系分组
		for (int j = 0;j < v;j++)
		{
			deque<int>q;
			for (int k = j;k <= V;k += v)
			{
				dp[i-1][k]-= k / v * w;
				while (!q.empty()&&dp[i-1][k]>dp[i-1][q.back()])
				{
					q.pop_back();
				}
				q.push_back(k);
				if ((k - q.front()) / v > s)q.pop_front();
				dp[i][k] = dp[i - 1][q.front()] + k / v * w;
			}
		}
	}
	printf("%d", dp[N][V]);
	return 0;
}