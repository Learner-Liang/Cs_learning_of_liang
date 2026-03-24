
/*给出了一个长度为N的序列，元素下标从 1 到 N，你需要处理如下两种询问。

​ "C a b c"表示给[a, b]区间中的值全部增加c(-10000 ≤ c ≤ 10000)。

​ "Q a b" 询问[a, b]区间中所有值的和。*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define lowbit(x) (x)&(-x)
using namespace std;
void _add(int* c, int x, int k, int n)
{
	while (x <= n)
	{
		c[x] += k;
		x += lowbit(x);
	}
	return;
}
int _query(int* c, int x)
{
	int sum = 0;
	while (x)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}
int main16()
{

	//(k-i+1)xi   的总和x表示差分数组中的元素——》（k+1）xi and -i*xi
	// 一个传统的差分数组，一个由i*xi的数组
	//解决区域性问题用线段数组非常方便，但是这里用树状数组
	int n,m;
	int a[100] = { 0 };
	int x[2][100] = { 0 };
	cin >> n >> m;
	for (int i = 1;i <= n;i++)cin >> a[i];
	for (int i = 1;i <= n;i++)
	{
		_add(x[0], i, a[i] - a[i - 1], n);
		_add(x[1], i, i * (a[i] - a[i - 1]), n);
	}

	for (int i = 1,a,b,c;i <= m;i++)
	{
		char ch;
		cin >> ch;
		if (ch == 'C')
		{
			cin >> a >> b >> c;
			_add(x[0], a, c, n);
			_add(x[0], b+1, -c, n);
			_add(x[1], a, c * a, n);
			_add(x[1], b + 1, -c * (b+1), n);
		}
		else
		{
			cin >> a >> b;
			int sum = 0;
			sum += (b + 1)*_query(x[0], b);
			sum -= (a)*_query(x[0], a - 1);
			sum -= _query(x[1], b);
			sum += _query(x[1], a - 1);
			cout << sum << endl;
		}
	}
	return 0;
}