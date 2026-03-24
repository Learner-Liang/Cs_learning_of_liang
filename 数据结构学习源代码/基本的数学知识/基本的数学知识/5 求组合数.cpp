#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int dp[1000][1000] = { 0 };
int mod = 10e9 + 7;
//递推法
void combination()
{
	for (int i = 0;i < 500;i++)
	{
		for (int j = 0;j <= i;j++)
		{
			if (!j)dp[i][j] = 1;
			else dp[i][j] = dp[i - 1][j] + dp[i - 1][j];
		}
	}
}
int quick_m(int a, int p, int mod)
{
	int ans = 1;
	while (p)
	{
		if (p & 1)
		{
			ans = ans * a % mod;
		}
		a = a * a % mod;
		p >>= 2;
	}
	return ans % mod;
}
//阶乘与其逆元
//预处理法
int f[1000] = { 0 }, inf[1000] = { 0 };
void pre_combination()
{
	f[0] = inf[0] = 1;
	for (int i = 1;i < 500;i++)
	{
		f[i] = f[i - 1] * i % mod;
		inf[i] = quick_m(i, mod - 2, mod) % mod;
	}
}

//卢卡斯定理
int C(int a, int b, int p)
{
	int pre = 1;
	for (int i = 1;i <= a;i++)
	{
		pre = pre * i % p;
	}
	pre = quick_m(b, p - 2, p) * quick_m(a - b, p - 2, p) % p;
	return pre;
}
int lukas(int a, int b, int p)
{
	if (a < p && b < p)
	{
		return C(a, b, p) % p;
	}
	else return lukas(a % p, b % p, p) * lukas(a / p, b / p, p);
}
int main()
{
	int a, b;
	cin >> a >> b;
	combination();
	cout << dp[a][b];
	return 0;
}