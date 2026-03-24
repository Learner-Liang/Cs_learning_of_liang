/*HZOJ334*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
/*Gcd(a,b)=gcd(a,b-a)=gcd(a-b,b)
gcd（a,b,c)=gcd(a,b,c-b)=gcd(a,b-a,c-b);
可以类比到整个差分数组
*/
//维护差分数组的最大公约数
#define int long long
int n, m, ans = 0;
int a[100] = { 0 };
int val[405] = { 0 }, c[405] = { 0 };
int gcd(int a, int b)
{
	if (!b)return a;
	return gcd(b, a % b);
}
void UP(int ind);
void build(int ind, int l, int r);
void modify(int ind, int l, int r, int x,int k);
void GCD(int ind,int l,int r,int x, int y);
int query(int ind, int l, int r, int x, int y);
int32_t main()
{
	cin >> n >> m;
	for (int i = 1;i <= n;i++)scanf("%lld", a + i);
	build(1,1,n);
	for (int i = 0,l,r,d;i < m;i++)
	{
		char ch[5];
		scanf("%s", ch);
		scanf("%s", ch);
		if (ch[0] == 'C')
		{
			scanf("%lld%lld%lld", &l, &r, &d);
			modify(1, 1, n, l, d);
			if (r + 1 <= n)modify(1, 1, n, r + 1, -d);
		}
		else
		{
			scanf("%lld %lld", &l, &r);
			ans=query(1, 1, n, 1, l);
			if(l+1<=r)GCD(1,1,n,l + 1, r);
			cout <<abs( ans) << endl;
		}
	}
	return 0;
}
void build(int ind, int l, int r)
{
	if (l == r)
	{
		val[ind] = a[l] - a[l - 1];
		c[ind] = a[l] - a[l - 1];
		return;
	}
	int mid = (l + r) / 2;
	build(ind * 2, l, mid);
	build(ind * 2 + 1, mid + 1, r);
	UP(ind);
	return;
}
void UP(int ind)
{
	val[ind] = val[ind * 2] + val[ind * 2 + 1];
	c[ind] = gcd(c[ind * 2], c[ind * 2 + 1]);
	return;
}
void modify(int ind, int l, int r, int x, int k)
{
	if (l == r)
	{
		val[ind] += k;
		c[ind] += k;
		return;
	}
	int mid = (l + r) / 2;
	if (x <= mid)modify(ind * 2, l, mid, x, k);
	else modify(ind * 2 + 1, mid + 1, r, x, k);
	UP(ind);
	return;
}
void GCD(int ind,int l,int r, int x, int y)
{
	if (x <= l && y >= r)
	{
		ans = gcd(ans, c[ind]);
		return;
	}
	int mid = (l + r) / 2;
	if (x <= mid)GCD(ind * 2, l, mid, x, y);
	if (y >mid)GCD(ind * 2 + 1, mid + 1, r, x, y);
	return;
}
int query(int ind, int l, int r, int x, int y)
{
	
	if (x <= l && y >= r)return val[ind];
	int sum = 0;
	int mid = (l + r) / 2;
	if (x <= mid)sum += query(ind * 2, l, mid, x, y);
	if (y > mid)sum += query(ind * 2 + 1, mid + 1, r, x, y);

	return sum;
}