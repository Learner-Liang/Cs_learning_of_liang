#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
//前缀和改成动态规划
int main26()
{
	int dp[100005] = { 0 };
	int n;
	cin >> n;
	int ans = -222222222;

	for (int i = 1;i <= n;i++)
	{
		cin >> dp[i];
		if (dp[i - 1] > 0)dp[i] += dp[i - 1];
		ans = max(ans, dp[i]);
	}
	cout << ans;
	return 0;
}