#include <iostream>
#include <queue>
#include <queue>
using namespace std;
#define max 1000000
//由于相同单词编号，因而统计单词出现次数
int node[max + 5][26] = { 0 };
int val1[max + 4] = { 0 };
int node_cnt = 1, root = 1;
char s[max + 5];
int fail[max + 5] = { 0 };

void insert_ac1(const char* s)
{
	int p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (node[p][ind] == 0)node[p][ind] = ++node_cnt;
		p = node[p][ind];
	}
	val1[p]++;
	return;
}
void build_ac1()
{
	//用head和tail模拟队列
	int p = root;
	queue<int>q;
	for (int i = 0;i < 26;i++)
	{
		//if (node[p][i] == 0)node[p][i]=root;
		fail[node[p][i]] = root;
		if (node[p][i] == 0)
		{
			//node[p][i] = root;
			continue;
		}
		q.push(node[p][i]);
	}
	while (!q.empty())
	{
		int temp = q.front();
		q.pop();
		for (int i = 0;i < 26;i++)
		{
			if (node[temp][i] == 0)
			{
				if (fail[temp] == 0)
					node[temp][i] = root;
				else
					node[temp][i] = node[fail[temp]][i];
				continue;
			}
			p = fail[temp];
			if (p == 0)p = root;
			else p = node[p][i];
			fail[node[temp][i]] = p;
			q.push(node[temp][i]);

		}
	}
	return;
}
int main12()
{
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		insert_ac1(s);
	}
	cin >> s;
	build_ac1();
	int ans = 0;
	int p = root, q;
	for (int i=0;s[i];i++)
	{
		int ind = s[i] - 'a';
		p = node[p][ind];
		q = p;
		while (q>1&&val1[q]!=-1)
		{
			ans += val1[q];
			val1[q] = -1;
			q = fail[q];
		}
	}
	cout << ans;
	return 0;
}