#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main20()
{
	//采用二进制
	int dp[10005] = { 0 };
	int V, N;
	cin >> V >> N;
	int v[10005], w[10005], s[10005];
	for (int i = 1,v,w,s;i <= N;i++)
	{
		scanf("%d%d%d", &v, &w, &s);
		for (int k = 1;s;s -= min(k,s), k *= 2)
		{
			k = min(k, s);
			for (int j = V;j >= k * v;j--)
			{
				dp[j] = max(dp[j], dp[j - k * v] + k * w);
			}
		}
	}

	return 0;
}