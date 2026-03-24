/*
【题目】7 容斥原理
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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int n, m;
int p[10] = { 0 };
int main()
{
	cin >> n >> m;
	for (int i = 0;i < m;i++)cin >> p[i];
	int res = 0;
	for (int i = 1;i < 1 << m;i++)
	{
		int t = 1, cnt = 0;
		for (int j = 0;j < m;j++)
		{
			if (i >> j & 1)
			{
				cnt++;
				if (t * p[j] > n)
				{
					t = -1;
					break;
				}
				t *= p[j];
			}
		}
		if (t != -1)
		{
			if (cnt % 2)res -= n / t;
			else res += n / t;
		}
	}

	return 0;
}