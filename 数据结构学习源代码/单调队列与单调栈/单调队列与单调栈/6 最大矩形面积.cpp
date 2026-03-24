/*
【题目】6 最大矩形面积
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
#include <stack>
#include <vector>
#include <deque>
using namespace std;
//˼άеߣȻǴһľ̵ľ
//ջֱάߵСڹϵ,һҲ
int main4()
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
	vector<long long>arr(n + 2),l(n+2),r(n+2);//ߴڳΪ0ľ
	for (int i = 1;i <= n;i++)
	{
		scanf("%lld", &arr[i]);
	}
	stack<int>q;
	q.push(0);
	for (int i = 1;i <= n;i++)
	{
		while (!q.empty() && arr[i] < arr[q.top()])
		{
			r[q.top()] = i;
			q.pop();
		}
		//l[i] = q.top();
		q.push(i);
	}
	//while (!q.empty())q.pop();
	//q.push(0);
	//for (int i = n;i>=0;i--)
	//{
	//	while (!q.empty() && arr[i] < arr[q.top()])
	//	{
	//		l[q.top()] = i;
	//		q.pop();
	//	}
	//	//r[i] = q.top();
	//	q.push(i);
	//}
	//ֶ
	while (!q.empty())
	{
		r[q.top()] = n+1;
		q.pop();
	}
	long long s = 0;
	for (int i = 1;i <= n;i++)
	{
		s = max(s, arr[i] * (r[i]-1 - l[i]));
	}
	cout << s;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}