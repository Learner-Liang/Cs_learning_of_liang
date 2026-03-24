/*
【题目】13 复杂版本
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
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
char s[20][75] = { 0 };
struct Node {
	vector<int>ind;
	int fail;
	int next[26] = { 0 };
}AC[800];
int cnt_ac[800] = { 0 }, node_cnt1 = 1, root_ = 1;
char S[7000] = { 0 };
int getNewNode()
{
	node_cnt1++;
	AC[node_cnt1].ind.clear();
	AC[node_cnt1].fail = 0;
	memset(AC[node_cnt1].next, 0,sizeof(int)* 26);
	return node_cnt1;
}
void init()
{
	node_cnt1 = 0, root_ = getNewNode();
	root_ = getNewNode();
	memset(cnt_ac, 0, sizeof(char)*800);
}
void insert2(const char* s , int i)
{
	int p = root_;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (AC[p].next[ind] == 0)AC[p].next[ind] = getNewNode();
		p = AC[p].next[ind];
	}
	AC[p].ind.push_back(i);
	return;
}
void build_ac2()
{
	queue<int>que;
	que.push(root_);
	int p;
	while (!que.empty())
	{
		p = que.front();
		int q;
		que.pop();
		if (AC[p].fail)
		{
			int I = AC[AC[p].fail].ind.size();
			for (int i = 0;i < I;i++) {
				AC[p].ind.push_back(AC[AC[p].fail].ind[i]);
			}
		}
		for (int i = 0;i < 26;i++)
		{
			if (AC[p].next[i] == 0)
			{
				if (AC[p].fail == 0)
					AC[p].next[i] = root_;
				else AC[p].next[i] = AC[AC[p].fail].next[i];
				continue;
			}
			q = AC[p].fail;
			if (q == 0)q = root_;
			else q = AC[q].next[i];
			AC[AC[p].next[i]].fail = q;
			que.push(AC[p].next[i]);
		}
	}
}
void find_long()
{
	int p = root_;
	for (int i = 0;S[i];i++)
	{
		int ind = S[i] - 'a';
		p = AC[p].next[ind];
		int I = AC[p].ind.size();
		for (int i = 0;i < I;i++)
		{
			cnt_ac[AC[p].ind[i]] += 1;
		}
	}
}
int main13()
{
	int n = 0;
	scanf("%d", &n);
	while (n)
	{
		init();
		for (int i = 0;i < n;i++)
		{
			cin >> s[i];
			insert2(s[i], i);
		}
		build_ac2();
		cin >> S;
		find_long();
		int ans = 0;
		for (int i = 0;i < n;i++)
		{
			if (cnt_ac[i] > ans)ans = cnt_ac[i];
		}
		cout << ans << endl;;
		for (int i = 0;i < n;i++)
		{
			if (cnt_ac[i] == ans)cout << s[i] << endl;
		}
		scanf("%d", &n);
	}
	return 0;
}