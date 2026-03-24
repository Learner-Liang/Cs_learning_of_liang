#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define lowbit(x) ((x)&(-x))
/*
如题，已知一个数列，你需要进行下面两种操作：
将某一个数加上x
求出某区间每一个数的和
*/
void add99(int* a, int* c,int i,int k, int n)
{
	a[i] += k;
	while (i <= n)
	{
		c[i] += k;
		i += lowbit(i);
	}
	return;
}
int query99(int x,int* c)
{
	int sum = 0;
	while (x)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}
int main9()
{
	int n, m;
	cin >> n >> m;
	int a[1000] = { 0 };
	int c[1000] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		int k = 0;
		cin >> k;
		add99(a, c, i, k,n);
	}
	for (int i = 1, w, x, y;i <= m;i++)
	{
		scanf("%d%d%d", &w, &x, &y);
		switch(w)
		{
		case 1:
		{
			add99(a, c, i, y,n);
			break;
		}
		case 2:
		{
			cout << query99(y, c) -query99(x-1,c)<< endl;
			break;
		}
		}
	}
	return 0;
}