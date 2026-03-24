/*
【题目】4 脱拓扑排序
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

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