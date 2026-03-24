#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
string word[2005];
bool is_valid(int i, int j)
{
	if (word[i].size() >= word[j].size())return false;
	for (int x = 0;word[i][x];x++)
	{
		if (word[i][x] != word[j][x])return false;
	}
	return true;
}
//p1481
int main28()
{
	int dp[2005] = { 0 };
	int n;
	cin >> n;
	int ans = 0;
	for (int i = 0;i < n;i++)
	{
		cin >> word[i];
		dp[i] = 1;
		for (int j = 0;j < i;j++)
		{
			if (is_valid(j, i))
				dp[i] = max(dp[j] + 1, dp[i]);
		}
		ans = max(ans, dp[i]);
	}
	return 0;
}