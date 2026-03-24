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
int num_oula(int n)//求质因数个数
{
	int ans = n;
	for (int i = 2;i <= n / i;i++)
	{
		if (n % i == 0)
		{
			ans = ans * (i - 1) / i;
			while (n % i == 0)n /= i;
		}
	}
	if (n > 1)ans *= (n - 1) / n;
	return ans;
}
int primes[10000] = { 0 }, cnt = 0;
int phi[10000] = { 0 };
bool st[10000] = { 0 };
int get_eulers(int n)//用线性筛法求1到n的欧拉函数之和
{
	int ans = 0;
	phi[1] = 1;
	for (int i = 2;i <= n;i++)
	{
		if (!st[i])
		{
			primes[cnt++] = i;
			phi[i] = i - 1;
		}
		for (int j = 0;primes[j] <= n / i;j++)
		{
			st[primes[j] * i] = 1;
			if (i % primes[j] == 0)
			{
				phi[primes[j] * i] = primes[j] * phi[i];
				break;
			}
			else
			{
				phi[i * primes[j]] = phi[i] * phi[primes[j]];
			}
		}
	}
	for (int i = 1;i <= n;i++)ans += phi[i];
	return ans;
}
int main()
{
	int n;
	cin >> n;
	cout << num_oula(n) << endl;
	cout << get_eulers(n) << endl;
	return 0;
}