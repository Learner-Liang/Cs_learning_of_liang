/*
【题目】7 借教室
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

// p1083
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>

using namespace std;
int n1, m1;
struct order {
	int d, s, t;
};
int x[1000] = { 0 };
int a[1000] = { 0 };
order ods[1000];
bool check(int mid)
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

	for (int i = 1;i <= n1;i++)
	{
		x[i] = a[i] - a[i - 1];
	}
	for (int i = 1;i <= mid;i++)
	{
		x[ods[i].s] -= ods[i].d;
		x[ods[i].t+1] += ods[i].d;
	}
	long long sum = 0;
	for (int i = 1;i <= n1;i++)
	{
		sum += x[i];
		if (sum < 0)return 1;
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
int binary_search(int l,int r)
{
	int mid;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (check(mid))r = mid;
		else l = mid + 1;
	}
	return l;
}
//ַļɣұr=m+1;
//ȫ0ָm+1λȫҪĽ 
int main7()
{
	//ַǰiΪ0ֲ㶩1ҵһ1
	//ǰ׺ͣвֺڽǰ׺͵ĲжÿǷڵ0
	//ֱӱҲԣٶȻܶ࣬ǰ׺
	cin >> n1 >> m1;
	for (int i = 1;i <=n1;i++)  scanf("%d", a + i);
	for (int i = 1;i <= m1;i++)  scanf("%d%d%d", &(ods[i].d), &ods[i].s, &ods[i].t);
	/*int flag = 1;
	long long sum = 0;
	for (int i = 1;i <= n;i++) x[i] = a[i] - a[i-1];*/
	/*int i;
	for (i = 1;i <= m;i++)
	{
		x[ods[i].s] -= ods[i].d;
		x[ods[i].t + 1] += ods[i].d;
		for (int j = 1;j <= ods[i].t;j++)
		{
			sum += x[j];
			if (sum < 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
		{
			break;
		}
		sum = 0;
	}
	if (flag == 0)cout << "-1" << endl << i;
	else cout << 0;*/
	int ind = binary_search(1, m1 + 1);
	if (ind!= m1+1)cout << "-1" << endl << ind;
	else cout << 0;
	return 0;
}