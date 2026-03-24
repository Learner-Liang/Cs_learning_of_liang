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
int x, y;
int ex_gcd(int& x, int& y, int a, int b)
{
	if (!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d = ex_gcd(y, x, b, a % b);
	y -= a / b * x;
	return d;
}
int n, x, y;
int a[10], m[10];
int main()
{
	cin >> n;
	int ans;
	for (int i = 0;i < n;i++)cin >> a[i] >> m[i];
	for (int i = 1;i < n;i++)
	{
		int d = ex_gcd(x, y, a[i], a[i - 1]);
		int k = (m[i - 1] - m[i]) / d;
		if (k * d == m[i] - m[i - 1])
		{
			a[i] = a[i] * a[i - 1] / d;
			m[i] = k * x * a[i] + m[i];
		}
		else
		{
			cout << "нч╫Б";
			break;
		}
	}
	ans = m[n - 1];
	return 0;
}