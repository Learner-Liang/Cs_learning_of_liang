/*
【题目】3独木船
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
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main3()
{
	int w, n, a[30005] = { 0 };
	cin >> w >> n;
	for (int i = 0;i < n;i++)
		cin >> a[i];
	int head = 0, tail = n - 1, ans = 0;
	sort(a, a + n);
	while (head <= tail)
	{
		if (a[tail] + a[head] <= w)
		{
			tail--;
			head++;

		}
		else
			tail--;
		ans++;
	}
	cout << ans;
	return 0;
}