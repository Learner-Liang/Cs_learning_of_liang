#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
int main13()
{
	//给出两个字符串，求其两个的最长公共子序列长度。
	//dp[i][j]表示第一个字符串以i为结尾，另一个以j为结尾,最长公共子串的数量
	//d[i][j]=Max(d[i-1][j],d[i][j-1],d[i-1][j-1]+a[i]==b[j]);
	string a, b;
	cin >> a >> b;
	int s1 = a.size(), s2 = b.size();
	int dp[1005][1005] = { 0 };
	for (int i = 0;i < s1;i++)
	{
		for (int j = 0;j < s2;j++)
		{
			dp[i][j] =max(dp[i - 1][j], dp[i][j - 1]);
			if (a[i] == b[j])dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
		}
	}
	printf("%d", dp[s1-1][s2-1]);
	return 0;
}