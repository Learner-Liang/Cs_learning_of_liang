#include <iostream>
#include <string>
using namespace std;
//国外叫KMP
//一个字符串与其每一个后缀的最长公共前缀长度
//next[i] = k;表示第i位开头的字符串顶多与第k位为结尾的字符串匹配，k也表示长度
int main19()
{
	string s;
	int z[10005] = { 0 };
	cin >> s;
	int n = s.size(), l = -1, r = -1;
	z[0] = n;
	for (int i = 1;i < n;i++)
	{
		if (i <= r)z[i] = min(r - i + 1, z[i - l]);
		while (z[i]+i < n && s[z[i]] == s[z[i] + i])z[i]++;
		if (i + z[i]-1>r)
		{
			l = i;
			r = i + z[i]-1;
		}
	}
	for (int i = 0;i < n;i++)
	{
		cout << z[i] << " ";
	}
	return 0;
}