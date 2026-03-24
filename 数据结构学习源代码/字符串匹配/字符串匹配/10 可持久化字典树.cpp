/*
【题目】10 可持久化字典树
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
#include <cmath>
#include <string>
using namespace std;
//ÿβ붼¼ı;
int rt[1005] = { 0 };//iڵ±
int ch[1005*30][26] = {0};//ÿڵʮ,ÿ26
int rt_cnt = 0;//ǰڵ
int val[1005 * 30] = { 0 };//ĳڵ㵥ʵ

void insert(int o, int n, char* s)
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

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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
int find(int a, int b, char* s)//ֵַĴ
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