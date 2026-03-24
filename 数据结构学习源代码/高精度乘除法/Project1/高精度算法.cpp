/*
【题目】高精度算法
【整体算法思路】
步骤1：读取输入并完成初始化。先把题目给的数字/字符串准确放进变量。
目的：只有输入含义搞清楚，后面 for/while 的边界与数组下标才不会写错。
步骤2：建立数据结构/状态定义（尤其是 DP 的 dp[i][j] 到底表示什么）。
目的：把“题目文字”翻译成“程序状态”；定义不清，转移方程一定写不对。
步骤3：执行核心算法（循环/递归/搜索/转移），把子问题答案逐步合成总答案。
目的：每一轮循环都要回答“我现在在解决哪个子问题，为什么这样更新是正确的”。
步骤4：输出结果并结束程序。输出下标必须和状态定义一一对应。
目的：返回题目要求的结果，完成一次完整求解。
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
// ߾ȴ*С
vector<int>multi(vector<int>arr, int a)
{
	vector<int>c;
	if (a == 0)
	{
		c.push_back(a);
		return c;
	}
	int t = 0;
	int n = arr.size();
	
	// 步骤3细化（核心循环解释）：for/while 的顺序不是随便写的，它决定“先用哪些已知结果”。
	// 顺序背后的原理：0/1 背包常用倒序防止同一物品被重复选；图最短路按当前最优点扩展才满足贪心前提。
	for (int i = 0;i < n;i++)
	{
		t = (arr[i]) * a+t;
		c.push_back(t%10);
		t /= 10;
	}
	while (t)
	{
		c.push_back(t % 10);
		t /= 10;
	}
	return c;
}
// ߾СԳ
vector<int>div(vector<int>arr, int b)
{
	vector<int>c;
	int t = 0;
	int n = arr.size();
	for (int i = n - 1;i >= 0;i--)
	{
		c.push_back((arr[i] + t * 10) / b);
		t = (arr[i] + t * 10) % b;
	}
	reverse(c.begin(), c.end());
	while (*c.end() == 0)c.pop_back();
	return c;
}

// ߾ȴ
vector<int>multi_multi(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size(), n2 = b.size();
	for (int i = 0;i < n1;i++)
	{
		for (int j = 0;j < n2;j++)
		{
			if (i + j >= c.size())c.push_back(a[i] * b[j]);
			// 步骤3细化（判断条件解释）：这个 if/while 是“题目约束”的程序化表达，用来过滤非法状态。
			// 为什么这么写：若不先判断就更新，常见后果是越界、重复使用元素或把不可能状态算进去。

			else c[i+j] += a[i] * b[j];
		}
	}
	int t = 0;
	int m = c.size();
	for (int i = 0;i < m || t;i++)
	{
		if(i<m)t = c[i] + t;
		if (i >= c.size())c.push_back(t % 10);
		else c[i] = t % 10;
		t /= 10;
	}
	return c;
}

int cmp(vector<int>a, vector<int>b)//Ƚ߾ĴС
{
	int n1 = a.size();
	int n2 = b.size();
	if (n1 != n2)return n1 < n2;
	for (int i = n1 - 1;i >= 0;i--)
	{
		if (a[i] != b[i])return a[i] < b[i];
	}
	return 0;//abʱ򷵻0
}

//߾ȴദ
vector<int>div_div(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size();
	int n2 = b.size();
	if (cmp(a,b))
	{
		c.push_back(0);
		return  c;
	}
	int n = n1-1;
	int m = n2 - 1;
	//ʱĬa>=b
	int k = 0;
	while (n >= m)
	{
		if (a[n] < b[m])
		{
			if(n!=0)//ע߽
			a[n-1] += a[n] * 10;
			n--;
			c.push_back(k);
			k = 0;
			continue;
		}
		int t = 0;
		int q = n - m;
		for (int i = 0;i <= m;i++)
		{
			a[q+i] -= b[i]+t;
			if (a[q + i] < 0)
			{
				a[q+ i] += 10;
				t = 1;
			}
			else
				t = 0;
		}
		k++;
	}
	reverse(c.begin(), c.end());
	while (c[c.size() - 1] == 0)c.pop_back();
	return c;
}
//ֱ
int main()
{
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行更新，把“已知子问题”推到“当前问题”。
// 目的：让小问题先解、大问题后解；若是 DP，要先说清状态定义，再写状态转移方程。
// 关键代码说明：max/min/松弛语句对应数学关系；循环顺序和 if 条件共同保证“不会漏解、不会重算、不会越界”。

	/*߾ȳ˷
	string a;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = multi(arr, b);
	
	// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
	for (auto x : arr)cout << x;*/
	//߾ȳ
	/*string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = div(arr, b);
	for (auto x : arr)cout << x;*/
	/*߾*߾
	string a, b;
	cin >> a >> b;
	vector<int>arr1, arr2;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	vector<int>c = multi_multi(arr1, arr2);
	int o = c.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << c[i];
	}*/
	//߾ȳԸ߾
	vector<int>arr1,arr2;
	string a, b;
	cin >> a >> b;
	vector<int>ans;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	ans = div_div(arr1, arr2);
	int o = ans.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << ans[i];
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}