/*
【题目】4数的计算
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
int main4()
{
	int n,half, ans=0;
	cin >> n;
	half = n / 2;
	int arr[1005] = { 0 };
	for (int i = 1;i <= n;i++)arr[i] = 1;
	for (int i = 2;i <= n;i++)
	{
		for (int j = i / 2;j >= 1;j--)
		{
			arr[i] += arr[j];
		}
	}
	cout << arr[n];
	return 0;
}