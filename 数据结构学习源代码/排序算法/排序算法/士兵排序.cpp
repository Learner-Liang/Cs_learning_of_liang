/*
【题目】士兵排序
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
#include <cstdlib>
#include <algorithm>
#define max 0x3f3f3f3f
using namespace std;
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
	int x[10005];
	int y[10005];
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		scanf("%d  %d", x + i, y + i);
	}
	sort(x, x + n);
	sort(y, y + n);
	int maxx = x[n-1], maxy = y[n-1], minx = x[0], miny = y[0];
	int mindistance1 = 0x3f3f3f3f,mindistance2=0x3f3f3f3f;
	for (int j = miny;j <= maxy;j++)
	{
		int temp1 = 0;
		for (int i = 0;i < n;i++)
		{
			temp1 += abs(y[i]-j);
		}
		if (temp1 < mindistance1)
	       mindistance1 = temp1;
	}
	//Żѡַƣһȡмֵ
	for (int i = minx-n;i <= maxx+n;i++)
	{
		int temp2 = 0;
		for (int j = 0;j < n;j++)
			temp2 += abs(x[j] - i - j);
		if (temp2 < mindistance2)
			mindistance2 = temp2;
	}
	//x-i-x[i],xiȥ±ٽлѡַ
	int distance = mindistance1 + mindistance2;
	cout << distance;
	return 0;
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
	using namespace std;
	int x[10005] = { 0 }, y[10005] = { 0 };
	int n;
	int main()
	{
		cin >> n;
		for (int i = 0;i < n;i++)scanf("%d %d", x + i, y + i);
		sort(x, x + n);
		sort(y, y + n);
		int ans = 0;
		for (int head = 0, tail = n - 1;head < tail;head++, tail--)ans += y[tail] - y[head];
		for (int i = 0;i < n;i++)x[i] -= i;
		sort(x, x + n);
		for (int head = 0, tail = n - 1;head < tail;head++, tail--)ans += x[tail] - x[head];
		cout << ans;

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
		return 0;
	}
}