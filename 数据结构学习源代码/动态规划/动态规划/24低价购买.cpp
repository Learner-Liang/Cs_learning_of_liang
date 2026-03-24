#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
//p1108
int main24()
{
//“低价购买”这条建议是在奶牛股票市场取得成功的一半规则。
//要想被认为是伟大的投资者，你必须遵循以下的问题建议:“低价购买；再低价购买”。每次你购买一支股票, 你必须用低于你上次购买它的价格购买它。
//买的次数越多越好!你的目标是在遵循以上建议的前提下，求你最多能购买股票的次数。
//你将被给出一段时间内一支股票每天的出售价，你可以选择在哪些天购买这支股票。每次购买都必须遵循“低价购买；再低价购买”的原则。写一个程序计算最大购买次数。
	int price[5005] = { 0 };
	int N;
	cin >> N;
	int dp[5005] = { 0 },  count[5005] = { 0 };
	price[0] = 0x7fffffff;
	int ans = 0;
	count[0] = 1;
	for (int i = 1;i <= N;i++)
	{
		scanf("%d", price + i);
		for (int j = 0;j < i;j++)
		{
			if (price[i] >= price[j])continue;
			dp[i] = max(dp[i], dp[j] + 1);
		}
		for (int j = 0;j < i;j++)
		{
			if (price[i] > price[j])continue;
			if (price[i] < price[j] && dp[j] + 1 == dp[i])
			{
				count[i] += count[j];
			}
			else if (price[i] == price[j] && dp[j] == dp[i])
				count[j] = 0;;
		}
		if (dp[ans] <= dp[i])ans = i;
	}
	//还要累加
	cout << dp[ans] <<count[ans]<< endl;
	return 0;
}