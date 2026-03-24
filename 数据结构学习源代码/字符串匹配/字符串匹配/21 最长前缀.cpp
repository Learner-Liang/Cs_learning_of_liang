/*
【题目】21 最长前缀
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
#include <string>
#include <vector>
#include<set>
using namespace std;
/*
    ģʽһıҵıǰ׺ԲģʽеַԪصǲģʽûеԪ
	һ P еԪؿԴԪؿظʹãһ s ôΪ s ԷֽΪ P еԪء
	ԪزһҪȫ֣ BBC ûг֣
	ٸӣ ABABACABAAB ԷֽΪ漯еԪأ{A,AB,BA,CA,BBC}
*/
int root3 = 1, cnt_front = 1;
int node2[1000][26] = { 0 }, val2[1000] = { 0 };
set<int>h;
int ans = 0;
void insert_front(string s)
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

	int p = root3;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)node2[p][ind] = ++cnt_front;
		p = node2[p][ind];
	}
	val2[p]+= 1;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return;
}
void find_value(string s)
{
	int x = *h.begin();
	h.erase(h.begin());
	int p = root3;
	for (int i = x;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)break;
		p = node2[p][ind];
		if (val2[p]&&h.find(i+1)==h.end())
		{
			h.insert(i+1);

			ans = max(i+1,ans);
		}
	}
	return;
}
int main21()
{
	string s = "", t;
	while(cin>>t)
	{
		if (t[0] == '.')break;
		insert_front(t);
	}
	while (cin >> t)s += t;
	int p = root3;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'A';
		if (node2[p][ind] == 0)break;
		p = node2[p][ind];
		if (val2[p]&&h.find(i+1)==h.end())
		{
			h.insert(i + 1);
			ans = max(i + 1,ans);
		}
	}
	while (!h.empty())find_value(s);
	cout << ans;
	return 0;
}