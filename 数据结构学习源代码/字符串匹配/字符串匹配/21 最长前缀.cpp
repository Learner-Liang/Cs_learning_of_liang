#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include<set>
using namespace std;
/*
    多个模式串，一个文本串，找到文本串的最长前缀，可以不包含模式串中的字符串元素但是不能有模式串中没有的元素
	如果一个集合 P 中的元素可以串起来（元素可以重复使用）组成一个序列 s ，那么我们认为序列 s 可以分解为 P 中的元素。
	元素不一定要全部出现（如下例中 BBC 就没有出现）。
	举个例子，序列 ABABACABAAB 可以分解为下面集合中的元素：{A,AB,BA,CA,BBC}
*/
int root3 = 1, cnt_front = 1;
int node2[1000][26] = { 0 }, val2[1000] = { 0 };
set<int>h;
int ans = 0;
void insert_front(string s)
{
	int p = root3;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)node2[p][ind] = ++cnt_front;
		p = node2[p][ind];
	}
	val2[p]+= 1;
	return;
}
void find_value(string s)
{
	int x = *h.begin();
	h.erase(h.begin());
	int p = root3;
	for (int i = x;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)break;
		p = node2[p][ind];
		if (val2[p]&&h.find(i+1)==h.end())
		{
			h.insert(i+1);

			ans = max(i+1,ans);
		}
	}
	return;
}
int main21()
{
	string s = "", t;
	while(cin>>t)
	{
		if (t[0] == '.')break;
		insert_front(t);
	}
	while (cin >> t)s += t;
	int p = root3;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)break;
		p = node2[p][ind];
		if (val2[p]&&h.find(i+1)==h.end())
		{
			h.insert(i + 1);
			ans = max(i + 1,ans);
		}
	}
	while (!h.empty())find_value(s);
	cout << ans;
	return 0;
}