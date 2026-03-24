#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int main14()
{
	//给出一个字符串S，问对字符串S最少切几刀，使得分成的每一部分都是一个回文串（注意：单一字符是回文串）
	//dp[i][j]表示第I个字符到j个字符的最少切法
	char s[1005];
	int dp[1005][1005] = { 0 };
	scanf_s("%s", s + 1,1005);
	int n = strlen(s + 1);
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= n;j++)
		{
			int l = i + j - 1;
			if (s[j] == s[l] && dp[j + 1][l - 1] == 0)dp[j][l] = 0;
			else
			{
				dp[j][l] = i;
				for (int k = j;k < l;k++)
					dp[j][l] = min(dp[j][l], dp[j][k] + dp[k + 1][l] + 1);
			}
		}
	}
	return 0;
}