#include <iostream>
#include <cmath>
using namespace std;
//编码是倒着的
//p=100110表示当前，模式串前6位，3，2位匹配成功
//p=(p<<1|1)&code   |1原因:当前新插入一位可能是模式串第一位字符
//d[a]表示模式串中字符出现的位置，也表示字符可以出现的位置

int shift_and(const char* s, const char* t)
{
	int d[128] = { 0 };
	for (int i = 0;t[i];i++)
	{
		d[t[i]] = d[t[i]] | 1 << i;
	}
	int p = 0;
	int n = strlen(t);
	for (int i = 0;s[i];i++)
	{
		p = (p << 1 | 1) & d[s[i]];
		if (p & (1 << (n - 1)))return i-n+1;
	}
	return -1;
}
int main6()
{
	char s[100], t[100];
	cin >> s >> t;
	cout << shift_and(s, t);
	return 0;
}