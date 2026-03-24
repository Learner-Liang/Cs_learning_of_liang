/*如题，已知一个数列，你需要进行下面两种操作：
将某区间每一个数加上 x；
求出某一个数的值。*/
//差分数组的前缀和与两点操作
//不是用树状数组维护原数组，而是用树状数组维护差分数组
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define lowbit(x) ((x)&(-x))
void add(int* c, int x, int k,int n)
{
	while (x <= n)
	{
		c[x] += k;
		x += lowbit(x);
	}
	return;
}
int query(int* c, int x)
{
	int sum = 0;
	while (x)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}
int main10()
{
	int c[1000] = { 0 };
	int n, m;
	cin >> n >> m;
	int temp = 0;
	for (int i = 1;i <= n;i++)
	{
		int k = 0;
		scanf("%d", &k);
		add(c, i, k - temp,n);
		temp = k;
	}
	for (int i = 1, u, x, y, k;i <= m;i++)
	{
		scanf("%d", &u);
		if (u == 1)
		{
			scanf("%d%d%d", &x, &y, &k);
			add(c, x, k,n);
			add(c, y + 1, -k,n);
		}
		else
		{
			scanf("%d", &x);
			cout << query(c, x);
		}
	}
	return 0;
}