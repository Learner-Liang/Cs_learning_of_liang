/*
【题目】9考前临时抱佛脚
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

#include <iostream>
#include <cstdlib>
using namespace std;
int arr2[4][25] = { 0 };
int s[4];
int ans4 = 0;
int dis3[4] = { 0 };
void dfs9( int i, int sum, int num,int p)//Ҫʱ̼ס
{
	if (num == 0)
	{
		ans4 = min(ans4, abs(dis3[i] - sum * 2));
		return;
	}
	for (int k = 1;k <= num;k++)
	{
		if(k)
		for (int j = p;j < s[i];j++)
		{
			dfs9( i, sum + arr2[i][j], k-1,j+1);
		}
	}
}
//void dfs9(int x, int l, int r, int k)
//{
//	if (k == s[x])
//	{
//		ans4 = min(ans4, max(l, r));
//		return;
//	}
//	l += arr2[x][k];
//	dfs9(x, l, r, k + 1);
//	l -= arr2[x][k];
//	r += arr2[x][k];
//	dfs9(x, l, r, k + 1);
//	r -= arr2[x][k];
//}
int main()
{
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	for (int i = 0;i < 4;i++)
	{
		cin >> s[i];
	}
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < s[i];j++)
		{
			cin >> arr2[i][j];
			dis3[i] += arr2[i][j];
		}
	}
	int all = 0;
	for (int i = 0;i < 4;i++)
	{
		ans4 = 10000;
		dfs9(i,0,s[i]/2,0);
		all += (dis3[i] + ans4) / 2;
		//cout << all << endl;
	}
	cout << all;
	/*for (int i = 0;i < 4;i++)
	{
		cin >> s[i];
	}
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < s[i];j++)
		{
			cin >> arr2[i][j];
		}
	}
	int all = 0;
	for (int i = 0;i < 4;i++)
	{
		ans4 = 10000;
		dfs9(i, 0, 0, 0);
		all += ans4;
	}
	cout << all;*/

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
using namespace std;

#define MAX_N 20
#define MAX_NUM 9999999
int s[10], sum[10] = { 0 };
int t[10][MAX_N + 5];
unordered_map<int, int> ind;

int solve(int k) {
	int ans = MAX_NUM;
	int T = (1 << s[k]);
	for (int i = 0; i < T; i++) {
		int j = i, l = 0, r = 0;
		while (j) {
			l += t[k][ind[j & -j]];
			j -= (j & -j);
		}
		r = sum[k] - l;
		ans = min(ans, max(l, r));
	}
	return ans;
}

int main() {
	for (int i = 0; i < 4; i++) cin >> s[i];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < s[i]; j++) {
			cin >> t[i][j];
			sum[i] += t[i][j];
		}
	}
	for (int k = 1, i = 0; i <= MAX_N; i++, k *= 2) ind[k] = i;
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		ans += solve(i);
	}
	cout << ans << endl;
	return 0;
}
