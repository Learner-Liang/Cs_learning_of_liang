#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
int c, n;
typedef struct point
{
	int x, y;
}point;
point P[505] = { 0 };
int temp[505] = { 0 };
bool check(int l);
bool check_y(int i, int j, int l);
int main()
{
	cin >> c >> n;
	for (int i = 0;i < n;i++)scanf("%d %d", &(P[i].x), &(P[i].y));
	sort(P, P + n, [&](const point a, const point b)->bool {
		if (a.x == b.x)return a.y < b.y;
		else return a.x < b.x;
		});
	int head = 1, tail = 10000, mid;
	while (head < tail)
	{
		mid = (head + tail) / 2;
		if (check(mid))tail = mid;
		else head = mid + 1;
	}
	printf("%d", tail);
	return 0;
}
bool check(int l)
{
	int j = 0;
	for (int i = 0;i < n;i++)
	{
		while (P[i].x - P[j].x >= l)j++;
		if (i - j + 1 >= c)
		{
			if (check_y(j, i, l))return 1;
		}
	}
	return false;
}
bool check_y(int i, int j, int l)
{
	int cnt = 0;
	for (int x = i;x <= j;x++)temp[cnt++] = P[x].y;
	sort(temp, temp + cnt);
	for (int k = c - 1;k < cnt;k++)
	{
		if (temp[k] - temp[k - c + 1] < l)
		{

			return 1;
		}
	}
	return false;
}