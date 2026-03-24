#include <iostream>
#include <cmath>
#include <string>
using namespace std;
//每次插入都记录发生改变的途径
int rt[1005] = { 0 };//第i棵子树根节点下标
int ch[1005*30][26] = {0};//假设每个节点最多三十个点,每个点最多26条边
int rt_cnt = 0;//当前节点编号
int val[1005 * 30] = { 0 };//某个节点单词的数量

void insert(int o, int n, char* s)
{
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		ch[n][ind] = ++rt_cnt;
		for (int j = 0;j < 26;j++)
		{
			if (ch[n][j])continue;
			ch[n][j] = ch[o][j];
		}
		n = ch[n][ind];
		o = ch[o][ind];
		val[n] = val[o];
	}
	val[n]++;
}
int find_once(int x, char* s)
{
	int p = rt[x];
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		p = ch[p][ind];
	}
	return val[p];
}
int find(int a, int b, char* s)//返回字符串出现的次数
{
	int x1 = find_once(b, s);
	int x2 = find_once(a - 1, s);
	return x1 - x2;
}
int main10()
{
	int n;
	cin >> n;
	char s[100];
	for (int i = 1;i <= n;i++)
	{
		cin >> s;
		rt[i] = ++rt_cnt;
		insert(rt[i], rt[i - 1], s);
	}
	int a, b;
	while (cin >> a >> b)
	{
		cin >> s;
		printf("from %d to %d, find %d\n", a, b, find(a,b,s));
	}
	return 0;
}