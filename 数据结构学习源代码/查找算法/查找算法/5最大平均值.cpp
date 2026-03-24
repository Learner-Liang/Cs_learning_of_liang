#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
long long n, m, p=0;
long long a[10000] = { 0 }, sum[10000] = { 0 };
bool check(int A)
{
	for (int i = 1;i <= n;i++)sum[i] = a[i] - A+sum[i-1];
	long long pre = 0;
	for (int i = m;i <= n;i++)
	{
		pre = min(pre, sum[i - m]);
		if (sum[i] - pre >= 0)return true;
	}
	return false;

}
int main()
{
	scanf("%lld %lld", &n, &m);
	for (int i = 1;i <= n;i++)
	{
		scanf("%lld", a + i);
		a[i] = 1000 * a[i];
		p = max(p, a[i]);
	}
	int head = 0, tail = p, mid;
	while (head < tail)
	{
		mid = (head + tail + 1) / 2;
		if (check(mid))head = mid;
		else tail = mid - 1;
	}
	printf("%d", head);
	return 0;
}