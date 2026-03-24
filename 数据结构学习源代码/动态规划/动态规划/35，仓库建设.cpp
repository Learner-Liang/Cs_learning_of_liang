#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main()
{
	int x[105] = { 0 }, p[105] = { 0 }, c[105] = { 0 };
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d%d%d", x + i, p + i, c + i);
	}
	int cost[105][105] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		for (int j = i-1;j>=1;j--)
		{
			cost[j][i] = cost[j + 1][i] + (x[i] - x[j]) * p[j];
		}
	}
	for (int i = 1;i <= n;i++)
	{

	}
	return 0;
}