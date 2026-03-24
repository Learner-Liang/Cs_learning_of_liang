/*
【题目】2 阶乘函数转非递归
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>
using namespace std;
struct data
{
	data(int g, int* p)
	{
		n = g;
		pre_ret = p;
		code = 0;
		return;
	}
	int n;
	int code, ret, * pre_ret;
};
int f(int n)
{
	if (n == 1)return 1;
	return n * f(n - 1);
}
int non_f(int n)
{
	stack<struct data>s;
	int ans;
	struct data c(n, &ans);
	s.push(c);
	while (!s.empty())
	{
		struct data& cur = s.top();
		switch (cur.code)
		{
		case 0:
		{
			if (cur.n == 1)
			{
				*(cur.pre_ret) = 1;
				s.pop();
			}
			else
			{
				cur.code = 1;
			}
			break;
		}
		case 1:
		{
			s.push(struct data(cur.n - 1, &cur.ret));
			cur.code = 2;
			break;
		}
		case 2:
		{
			*cur.pre_ret = cur.n * cur.ret;
			s.pop();
			break;
		}
		}
	}
	return ans;
}
int main()
{
	int n;
	while (1)
	{
		cin >> n;
		cout << non_f(n) << endl;
	}
	return 0;
}