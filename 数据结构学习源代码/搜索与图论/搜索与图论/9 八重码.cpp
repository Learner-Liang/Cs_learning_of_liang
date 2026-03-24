/*
【题目】9 八重码
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
#include <unordered_map>
#include <string>
using namespace std;
string s;
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int bfs()
{
	string end = "12345678X";
	queue<string>q;
	unordered_map<string, int>dis;
	dis[s] = 0;
	q.push(s);
	while (q.size())
	{
		string temp = q.front();
		if (temp == end)return dis[temp];
		q.pop();
		int t = 0;
		while (temp[t] == 'X')t++;
		int line = t / 3, column = t % 3;
		for (int i = 0;i < 4;i++)
		{
			int l = line + dx[i], c = column + dy[i];
			string te = temp;
			if (l <= 2 && l >= 0 && c <= 2 && c >= 0)
			{
				char c = temp[t];
				int position = l * 3 + c;
				te[t] = te[position];
				te[position] = c;
				if (dis.find(te) != dis.end())
				{
					dis[te] = dis[temp] + 1;
					q.push(te);
				}
			}
		}
	}
	return -1;
}
int main()
{
	char c;
	for (int i = 0;i < 9;i++)
	{
		cin >> c;
		s += c;
	}
	return 0;
}