#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
int main23()
{
	int n, M;
	cin >> n >> M;
	long long sum[1000005] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		scanf("%lld", sum + i);
		sum[i] += sum[i - 1];
	}
	long long dp[1000005] = { 0 };
	int q[1000005] = { 0 };
	//dp[i]=dp[j]-sum[j]+sum[i]+M;后面两项为固定值，前面为维护值
	//但是此题中存在混合值，因而要用斜率优化
	//JZOJ:52
	int head = 0, tail = 0;
	q[tail++] = 0;
	for (int i = 1;i <= n;i++)
	{
		while (tail - head >= 2 && (dp[q[head + 1]] + sum[q[head + 1]] * sum[q[head + 1]] - dp[q[head]] - sum[q[head]] * sum[q[head]]) * 1.0 / 
			(sum[q[head + 1]] - sum[q[head]])
			< 2 * sum[i])
		{
			head += 1;
		}
		dp[i] = dp[q[head]] + (sum[i] - sum[q[head]]) * (sum[i] - sum[q[head]])+M;
		//接下来判断斜率是否单增
		//压入队列
	}
	return 0;
}