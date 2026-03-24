//路径扩展；两个单词存在重叠部分：d[x][y]
//龙的长度:L+len[y]-d[x][y]
//判断单词使用次数:vis数组：回溯时候，还要-1
#include <iostream>
#include <string>
using namespace std;
string s[25];
int d[25][25] = { 0 };
int vis1[25] = { 0 };
int f(string s1, string s2)
{
	int k = s1.size();
	int k1 = s2.size();
	for (int i = k - 1;i >= 1;i--)//两个单词不能完全重合+
	{
		int I = k - i;
			for (int j = 0;j < I;j++)
			{
				if (s1[i + j] != s2[j])break;
				if (j == I - 1) return I;
			}
	}
	return 0;
}
int ans1 = 0;
void dfs5(int now, int sum,int n)
{
	if (sum > ans1)ans1 = sum;
	for (int i = 0;i < n;i++)
	{
		if (d[now][i]==0 || vis1[i] == 2)continue;
		vis1[i]++;
		dfs5(i,sum+ s[i].size() - d[now][i],n);
		vis1[i]--;
	}
}
int main6()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		cin >> s[i];
	}
	int ch;
	cin >> ch;
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;i < n;i++)
		{
			d[i][j] = f(s[i], s[j]);
		}
	}
	for (int i = 0;i < n;i++)
	{
		if (s[i][0] != ch) continue;
		vis1[i]++;
		dfs5(i, s[i].size(),n);
		vis1[i]--;
	}
	cout << ans1 << endl;
	return 0;
}