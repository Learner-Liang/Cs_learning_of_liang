/*
【题目】18 字符串哈希
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
#include <unordered_map>
#include<vector>
#include<string>
using namespace std;
/*
如题，给定 N 个字符串（第 i 个字符串长度为 Mi​，
字符串内包含数字、大小写字母，大小写敏感），请求出 N 个字符串中共有多少个不同的字符串。

 */
//老实计算出哈希值
int getHash_code(string s)
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

	int base = 90, h = 0;
	for (int i = 0;s[i];i++)
	{
		h = (h * base + (s[i]-'0'));
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return h;
}
int main18()
{
	int n;
	cin >> n;
	string s = { 0 };
	int ans = 0;
	unordered_map<int, vector<string>>h;
	int hash__code = 0;
	for (int i = 0;i < n;i++)
	{
		cin >> s;
		hash__code = getHash_code(s);
		if (h.find(hash__code) == h.end())
		{
			h[hash__code].push_back(s);
			ans++;
		}
		else
		{
			int flag = 1;
			for (auto i : h[hash__code])
			{
				if (i != s)continue;
				flag = 0;
				break;

			}
			if (flag)
			{
				h[hash__code].push_back(s);
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}