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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	/*߾ȳ˷
	string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = multi(arr, b);
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

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}