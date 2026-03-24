/*#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main()
{
	set<int>s;
	vector<vector<int>>g(2005);
	vector<int>b(2005);
	int n,m;
	cin >> n >> m;
	for (int i = 0;i < m;i++)
	{
		int a, c;
		cin >> a>>c;
		b[c] += 1;
		g[a].push_back(c);
	}
		for (int i = 1;i <= n;i++)
		{
			if (b[i] == 0)
			{
				s.insert(i);
			}
		}
		while (s.size() > 0)
		{
			int val = *s.begin();
			s.erase(s.begin());
			while (g[val].size() > 0)
			{
				int temp = *g[val].begin();
				g[val].erase(g[val].begin());
				b[temp] -= 1;
				if (b[temp] == 0) s.insert(temp);
			}
			cout << val;
			if(s.size()) cout<<' ';
		}
	return 0;
}*/#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
using namespace std;
vector<vector<int>>g(2005);
int debug[2005] = { 0 };
int main()
{
	int n, m;
	cin >> n >> m;
	set<int>s;
	for (int i = 0, a, b;i < m;i++)
	{
		cin >> a >> b;
		debug[b]++;
		g[a].push_back(b);
	}
	for (int i = 1;i <= n;i++)
	{
		if (debug[i] == 0)s.insert(i);
	}
	int cur, k;
	while (!s.empty())
	{
		cur = *s.begin();
		k = g[cur].size();
		s.erase(s.begin());
		for (int i = 0;i < k;i++)
		{
			debug[g[cur][i]] -= 1;
			if (debug[g[cur][i]] == 0)s.insert(g[cur][i]);
		}
		cout << cur;
		if (!s.empty())cout << " ";
	}
	return 0;
}