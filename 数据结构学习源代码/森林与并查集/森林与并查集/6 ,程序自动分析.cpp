/*
【题目】6 ,程序自动分析
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class unionset {
public:
	unionset(int n) :p(n + 1)
	{
		for (int i = 0;i <= n;i++)
			p[i] = i;
	}
	int find(int a)
	{
		if (p[a] == a)return a;
		return p[a] = find(p[a]);
	}
	void merge(int a, int b)
	{
		int aa = find(a), bb = find(b);
		if (aa == bb)return;
		p[a] = bb;
		return;
	}
	vector<int>p;
};
typedef struct Node
{
	int i, j, e;
}Node;
//int find_same(unionset& s, int n);
int solve()
{
	int n;
	scanf("%d", &n);
	vector<Node>N(n);
	unordered_map<int,int>m;
	int cnt = 0;
	for (int i = 0;i < n;i++)
	{
		scanf("%d%d%d", &N[i].i, &N[i].j, &N[i].e);
		if (m.find(N[i].i) == m.end()) m[N[i].i] = cnt++;
		if (m.find(N[i].j) == m.end()) m[N[i].j] = cnt++;
	}
	unionset u(2 * n);
	for (int i = 0;i < n;i++)
	{
		if (N[i].e == 0)continue;
		u.merge(m[N[i].i], m[N[i].j]);
	}
	for (int i = 0;i < n;i++)
	{
		if (N[i].e == 1)continue;
		if (u.find(m[N[i].i]) == u.find(m[N[i].j]))
			return 0;
	}
	return 1;
}
int main()
{
	int n;
	cin >> n;
	while (n--)
	{
		if (solve())printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
//��������̫���޷�����
/*int find_same(unionset& s, int n)
{
	if (n == 0)return 1;
	int i, j, e;
	scanf("%d%d%d", &i, &j, &e);
	if (e == 1)
	{
		s.merge(i, j);
		return find_same(s, n - 1);
	}
	else
	{
		if (find_same(s, n - 1))
		{
			if (s.find(i) != s.find(j))
				return 1;
		}
		return 0;
	}
}*/



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;
typedef pair<int, int> P;
int t, n;
int find(vector<int>& fa, int x)
{
	if (fa[x] == x)return x;
	fa[x] = find(fa, fa[x]);
	return fa[x];
}
void merge(vector<int>& fa, int a, int b)
{
	int aa = find(fa, a), bb = find(fa, b);
	if (aa == bb)return;
	fa[aa] = bb;
	return;
}
int main()
{
	cin >> t;
	for (int i = 0;i < t;i++)
	{
		cin >> n;
		unordered_map<int, int>m;
		set<P>s;
		int k = n * 2 + 2, cnt = 0;
		vector<int>fa(k);
		for (int j = 0;j < k;j++)fa[j] = j;
		for (int j = 0, a, b, c;j < n;j++)
		{
			cin >> a >> b >> c;
			if (m.find(b) == m.end())m[b] = cnt++;
			if (m.find(a) == m.end())m[a] = cnt++;
			if (c == 1)merge(fa, m[a], m[b]);
			else s.insert(P{ m[a],m[b] });
		}
		int flag = 1;
		for (auto xx : s)
		{
			int x = xx.first, y = xx.second;
			int aa = find(fa, x), bb = find(fa, y);
			if (aa != bb)continue;
			else
			{
				flag = 0;
				break;
			}
		}
		if (flag)printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}