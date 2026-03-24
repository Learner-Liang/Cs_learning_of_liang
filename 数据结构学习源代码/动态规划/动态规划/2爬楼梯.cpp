/*
【题目】2爬楼梯
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
#include <algorithm>
#include <vector>
using namespace std;
int main2()
{
	int n;
	cin >> n;
	int f[505] = { 0 };
	f[1] = 0;
	f[2] = 1;
	f[3] = 1;
	for (int i = 4;i <= n;i++)
	{
		if (f[i - 2])f[i] += f[i - 2];
		if (f[i - 3])f[i] += f[i - 3];
	}
	cout << f[n];
	return 0;
}