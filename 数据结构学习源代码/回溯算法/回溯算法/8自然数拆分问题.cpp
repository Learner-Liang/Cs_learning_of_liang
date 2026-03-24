/*
【题目】8自然数拆分问题
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
using namespace std;
int arr1[10] = { 0 };
void dfs8(int max, int n, int mis)
{
	if (mis == 0)
	{
		if (n < 2)return;
		for (int i = 0;i < n;i++)

		{
			printf("%d", arr1[i]);
			if (i != n - 1)printf("+");
		}
		cout << endl;
		return;
	}
	if (max > mis)return;
	for (int i = max;i <= mis;i++)
	{
		arr1[n] = i;
		dfs8(i, n + 1, mis - i);
	}
	return;
}
int main8()
{
	int n;
	cin >> n;
	dfs8(1, 0, n);
	return 0;
}