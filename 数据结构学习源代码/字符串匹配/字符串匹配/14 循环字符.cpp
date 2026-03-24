#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//HZOJ 278
//遍历一个字符串，前I为能被什么前缀循环构成，输出位置与次数
using namespace std;
int main14()
{
	int L;
	cin >> L;
	char s[100005] = { 0 };
	int next[100005] = { 0 };
	scanf("%s", s);
	int  j = -1;
	next[0] = -1;
	for (int i = 1;s[i];i++)
	{
		while (j != -1 && s[i] != s[j+1])j = next[j];
		if (s[i] == s[j+1])j++;
		next[i] = j;
		int n = i + 1, m = i - next[i];
		if (n % m == 0&&n/m>=2)printf("%d %d\n", n, n / m);
	}
	return 0;
}