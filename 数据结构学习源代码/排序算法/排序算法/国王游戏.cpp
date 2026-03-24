/*
【题目】国王游戏
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

//΢:õi+1λΪiλ㣬Եֳ֪˻Сķǰ
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define SIZE 10000
typedef struct human
{
	int l, r;
};
vector<int>ans, temp;
//˷
void multipy(int x);
vector<int>divide(int x);
vector<int>compare(vector<int>a, vector<int>b);
human m[10005] = { 0 };
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

	int n;
	cin >> n;
	for (int i = 0;i <= n;i++)scanf("%d %d", &m[i].l, &m[i].r);
	sort(m + 1, m + n + 1, [&](human a, human b)->bool
		{
			return a.l * a.r < b.l * b.r;
		});
	temp.push_back(m[0].l);
	for (int i = 1;i <= n;i++)
	{
		ans = compare(ans, divide(m[i].r));
		multipy(m[i].l);
	}
	printf("%d", ans[ans.size() - 1]);
	for (int i = ans.size() - 2;i >= 0;i--)printf("%4d", ans[i]);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
void multipy(int x)
{
	int n = temp.size();
	int t = 0;
	for (int i = 0;i < n;i++)
	{
		temp[i] = temp[i] * x + t;
		temp[i] = temp[i] % SIZE;
		t = temp[i] / SIZE;
	}
	while (t)
	{
		temp.push_back(t % SIZE);
		t /= SIZE;
	}
	return;
}
vector<int>divide(int x)
{
	vector<int>t = temp;
	int g = 0;
	for (int i = t.size() - 1;i >= 0;i--)
	{
		t[i] += g * SIZE;
		g = t[i] % x;
		t[i] /= x;
	}
	while (!t.empty() && t.back() == 0)t.pop_back();
	if (t.empty()) {
		t.push_back(0);
	}
	return t;
}
vector<int>compare(vector<int>a, vector<int>b)
{
	int n1 = a.size(), n2 = b.size();
	if (n1 != n2)return n1 < n2 ? b : a;
	for (int i = n1 - 1;i >= 0;i--)
	{
		if (a[i] != b[i])return a[i] > b[i] ? a : b;
	}
	return a;
}