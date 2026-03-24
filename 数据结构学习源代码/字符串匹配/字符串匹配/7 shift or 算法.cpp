#include <iostream>
#include <cmath>
using namespace std;
//有效位用0表示
//优化了左移和或1的操作
//p=(p<<1)|d[s[i]]
//左移的时候自带一个0
int shift_or(const char* s, const char* t)
{
	int d[128] = { 0 };
	for (int i = 0;t[i];i++)d[t[i]] = d[t[i]] | 1 << i;
	for (int i = 0;i < 128;i++)d[i] = ~d[i];
	//优化方法
	memset(d, -1, 128);
	for (int i = 0;t[i];i++)d[i] = d[i] & (~(1 << i));
	int n = strlen(t);
	int p = 0;
	for (int i = 0;s[i];i++)
	{
		p = (p << 1) | d[s[i]];
		if (!(p & (1 << (n - 1))))return i-n+1;
	}
	return -1;
}
int main7()
{
	char s[100], t[100] = { 0 };
	cin >> s >> t;
	cout << shift_or(s, t);
	return 0;
}