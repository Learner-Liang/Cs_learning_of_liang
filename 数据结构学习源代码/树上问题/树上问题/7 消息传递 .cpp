/*
【题目】7 消息传递 
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
#include <algorithm>
using namespace std;
/*ȼɭϣ˹֮⣬ÿ˾ֻһֱϼȻûϼ
 A  B ϼB  C ϼô A  C ϼԲĹϵA  B ϼB Ҳ A ϼ

ʼʱ 0Ҫľ 1 λʱһϢĳһˣ
ɢϢһʱ䵥λУκһѾӵϢˣ԰Ϣһֱϼֱ

ڣ֪
Ҫ೤ʱ䣬Ϣܴˣ
ҪʹϢڴݹĵʱ̣ɹѡЩ*/
struct edge
{
	int f = 0, s = 0;
}e[100];
int cnt = 0;
int nm;
int dp[100] = { 0 }, head[100] = { 0 };
int num[100] = { 0 };
int tail = -1;
void add( int a, int b)
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

	e[++cnt] = { b,head[a] };
	head[a] = cnt;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return;
}
void getDp(int f, int s);
void initdp();
int g = 1;
int main7()
{
	cin >> nm;
	for (int i = 2,a;i <= nm;i++)
	{
		scanf("%d", &a);
		add(a, i);
		add(i, a);
	}
	int mi = 0x3f3f3f3f;
	//öÿһΪڵĸڵֵ
	for (int i = 1;i <= nm;i++)
	{
		initdp();
		getDp(0,i);
		if (mi < dp[i])continue;
		else if (mi == dp[i])
		{
			num[++tail] = i;
		}
		else
		{
			mi = dp[i];
			tail = -1;
			num[++tail] = i;
		}
	}
	cout << mi << endl;
	for (int i = 0;i <= tail;i++)
		cout << num[i] << " ";
	return 0;
}
void getDp(int f, int s)
{
	for (int p = head[s];p;p = e[p].s)
	{
		int to = e[p].f;
		if (to == f)continue;
		getDp(s, to);
		dp[s] = max(dp[s], dp[to]+1);//ܴȵֵΪvector洢
	}
	return;
}
void initdp()
{
	for (int i = 1;i <= cnt;i++)dp[i] = 0;
	return;
}