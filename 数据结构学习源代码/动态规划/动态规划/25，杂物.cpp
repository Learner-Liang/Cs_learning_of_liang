#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
//p1113
int main25()
{
	vector<int>len(10005, 0);
	vector<int>dp(10005, 0);
	dp[0]=0;
	int n;
	cin >> n;
	for (int i = 1,a;i <= n;i++)
	{
		scanf("%d", &a);
		scanf("%d", &a);
		len[i] = a;
		scanf("%d", &a);
		dp[i] = min(dp[i], dp[a] + len[i]);
		while (a)
		{
			scanf("%d", &a);
			if(a)dp[i] = max(dp[i], dp[a] + len[i]);
		}
	}
	cout << dp[n];
	return 0;
}