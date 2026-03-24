/*
【题目】7 Bellmm_Ford
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
#include <cstring>
using namespace std;
int n, m, k;
typedef struct Edge
{
	int a, b, w;
}Edge;
Edge edge[100];
int dis[100], backup[100];
int Bellmm_Ford()
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	for (int i = 0;i < k;i++)
	{
		memcpy(backup, dis, sizeof(dis));
		for (int j = 0;j < m;j++)
		{
			int a = edge[j].a, b = edge[j].b, w = edge[j].w;
			dis[b] = min(dis[b], backup[a] + w);
		}
	}
	if (dis[n] > 0x3f3f3f3f / 2)return -1;
	return dis[n];
}
int main()
{
	cin >> n >> m >> k;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		edge[i] = { x,y,z };
	}
	return 0;
}