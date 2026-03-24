#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
int mian18()
{
	char s[500005];
	scanf("%s", s + 1);
	//枚举最后一刀切的位置
	int n = strlen(s + 1);
	//dp[i]，切的最后一部分为回文串
	int dp[500005] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		dp[i] = i;
		//判断从1到i是否是回文串
		// 是的话赋值为0，不是退出
		//1到i-1最后一刀的位置枚举，判断最后一刀的位置，之后部分判断是否是回文，不是回文退出
	}
	return 0;
}