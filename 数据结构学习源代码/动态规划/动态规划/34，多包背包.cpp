#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main34()
{
	/*他们一共有 K 个人，每个人都会背一个包。这些包 的容量是相同的，都是 V。可以装进背包里的一共有 N 种物品，每种物品都有 给定的体积和价值。

		在 DD 看来，合理的背包安排方案是这样的： 
		每个人背包里装的物品的总体积恰等于包的容量。 每个包里的每种物品最多只有一件，但两个不同的包中可以存在相同的物品。

		任意两个人，他们包里的物品清单不能完全相同。 在满足以上要求的前提下，所有包里的所有物品的总价值最大是多少呢？*/
	int K, V, N;
	cin >> K >> V>>N;
	//前k种最优方案
	int dp[5005][55] = { 0 };//容量前k优解值,第二位表示第几个解
	//刷表发省略了前i个物品
	dp[0][0] = 1;//方案数量
	//dp[i][0]表示i的方案数量
	dp[0][1] = 0;
	int temp[55] = { 0 };
	for (int i = 0, v, w;i < N;i++)
	{
		cin >> v >> w;

		for (int j = V;j >= v;j--)
		{
			int p1 = 1, p2 = 1, t = 1;
			int n1 = dp[j][0], n2 = dp[j - v][0];
			while (p1 <= n1 || p2 <= n2)
			{
				if (p2 > n2 || ((p1 <= n1 && dp[j][p1] >= dp[j - v][p2] + w))) {
					temp[t++] = dp[j][p1++];
				}
				else {
					temp[t++] = dp[j - v][p2++] + w;
				}
				if (t > K) break;
			}
			temp[0] = t - 1;
			memcpy(dp[j], temp, sizeof(int) * t);
		}

	}
	return 0;
}