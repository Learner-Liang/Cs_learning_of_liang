/*
给出一个长度为 n 的序列 a，选出其中连续且非空的一段使得这段和最大。
*/
#include <iostream>
using namespace  std;
/*
    区间--,j]中,找到j前面最的最值，即可找到区间的最值
*/
int main3()
{
	int n;
	cin >> n;
	int s[10000] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		cin >> s[i];
		s[i] += s[i - 1];
	}
	int ans = -33333333;
	int min_ = 0;
	for (int i = 1;i <= n;i++)
	{
		ans = max(ans, s[i] - min_);
		min_ = min(s[i], min_);
	}
	cout << ans;

	//取前面区间的正数
	//int dp[100005] = { 0 };
	//int n;
	//cin >> n;
	//int ans = -33333333;
	//for (int i = 1;i <= n;i++)
	//{
	//	cin >> dp[i];
	//	if (dp[i - 1] > 0)dp[i] += dp[i - 1];
	//	ans = max(ans, dp[i]);
	//}
	//cout << ans;
	return 0;
}