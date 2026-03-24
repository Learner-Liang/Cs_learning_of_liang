/*
【题目】8 双生序列
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
int double_vector(vector<int>A, vector<int>B)
{
	int n = A.size();
	deque<int>q1, q2;
	for (int i = 0;i < n;i++)
	{
		while (!q1.empty() && A[i] < A[q1.back()])q1.pop_back();
		while (!q2.empty() && B[i] < B[q2.back()])q2.pop_back();
		if (q1.size()!=q2.size())return i;
		q1.push_back(i);
		q2.push_back(i);
	}
	return n;
}
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
	vector<int>A(n), B(n);
	for (int i = 0;i < n;i++)cin >> A[i] >> B[i];
	int ans = double_vector(A, B);
	cout << ans;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}