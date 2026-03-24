#include <iostream>
using namespace std;
//在给定的 N 个正整数 A1，A2……AN 中选出两个进行异或运算，得到的结果最大是多少？
//从高到低尽量保证每一位不一样
//每一位，不同取1，相同取0
//意思就是匹配前缀
int NOde[10000][2] = { 0 };
int cnt_A = 1;
void insert(int x)
{
	int root = 1;
	for (int i = 30;i>=0;i--)
	{
		int ind = !!(x &(1<<i));
		//也可以分开讨论
		if (NOde[root][ind] == 0)NOde[root][ind] = ++cnt_A;
		root = NOde[root][ind];
	}
}
int quert(int k)
{
	int k_ = ~k;
	int ans = 0;
	int p = 1;
	for (int i = 30;i>=0;i--)
	{
		int ind = !!(k_ & (1 << i));
		if (NOde[p][ind] != 0)
		{
			p = NOde[p][ind];
			ans |= (1 << i);
		}
		else
		{
			p = NOde[p][!ind];
		}
		
	}
	return ans;
}
int main17()
{
	int n;
	cin >> n;
	int ans = 0;
	int k;
	cin >> k;
	insert(k);
	for (int i = 1;i < n;i++)
	{
		cin >> k;
		ans = max(ans, quert(k));
		insert(k);
	}
	ans = max(ans, quert(k));
	cout << ans;
	return 0;
}