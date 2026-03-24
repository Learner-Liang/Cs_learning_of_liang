/*
【题目】高精度算法
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
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
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
			// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
			// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

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