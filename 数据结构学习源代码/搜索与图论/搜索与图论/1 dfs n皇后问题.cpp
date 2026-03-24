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
int n;
bool col[100] = { 0 }, dg[100] = { 0 }, udg[100] = { 0 };
void dfs(int line)
{
	if (line == n + 1)
	{
		return;
	}
	for (int i = 1;i <= n;i++)
	{
		if (col[i])continue;
		if (dg[line + i - 1] == 0 && udg[i >= line ? line + i - n : line - i + n] == 0)
		{
			col[i] = 1;
			dg[line + i - 1] = 1;
			udg[i >= line ? line + i - n : line - i + n] = 1;
			dfs(line + 1);
			dg[line + i - 1] = 0;
			udg[i >= line ? line + i - n : line - i + n] = 0;
			col[i] = 0;
		}
	}
}
bool line[20] = { 0 }, column[20] = { 0 }, dg[20] = { 0 }, udg[20] = { 0 };
void dfs_1(int x, int y, int num)
{
	if (y == n)
	{
		x++;
		y = 0;
	}
	if (x == n)
	{
		if (num == n)
		{
			//输出
			return;
		}
	}
	//不放
	dfs_1(x, y + 1, num);
	//放
	if (line[y] == 0 && column[x] == 0 && dg[x + y] == 0 && udg[n - y + x] == 0)
	{
		line[y] = 1;
		column[x] = 1;
		dg[x + y] = 1;
		udg[n - y + x] = 1;
		dfs_1(x, y + 1, num + 1);
		line[y] = 0;
		column[x] = 0;
		dg[x + y] = 0;
		udg[n - y + x] = 0;
	}
}
int main()
{
	cin >> n;
	dfs(1);
	return 0;
}