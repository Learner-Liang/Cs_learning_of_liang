#include <iostream>
#include <unordered_map>
#include<vector>
#include<string>
using namespace std;
/*
如题，给定 N 个字符串（第 i 个字符串长度为 Mi​，
字符串内包含数字、大小写字母，大小写敏感），请求出 N 个字符串中共有多少个不同的字符串。

 */
//老实计算出哈希值
int getHash_code(string s)
{
	int base = 90, h = 0;
	for (int i = 0;s[i];i++)
	{
		h = (h * base + (s[i]-'0'));
	}
	return h;
}
int main18()
{
	int n;
	cin >> n;
	string s = { 0 };
	int ans = 0;
	unordered_map<int, vector<string>>h;
	int hash__code = 0;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		hash__code = getHash_code(s);
		if (h.find(hash__code) == h.end())
		{
			h[hash__code].push_back(s);
			ans++;
		}
		else
		{
			int flag = 1;
			for (auto i : h[hash__code])
			{
				if (i != s)continue;
				flag = 0;
				break;

			}
			if (flag)
			{
				h[hash__code].push_back(s);
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}