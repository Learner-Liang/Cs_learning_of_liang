//全排列
//搜索剪枝
//状态压缩：二进位权值标记
//排序状态压缩
#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;
typedef struct Node
{
	double x, y;
}Node;
Node p[20];
int ind[70000] = { 0 };//用数组模拟哈希表
double dp[70000][20] = {0};//dp[x][y],x表示其所在位置以及该位置之前的点的坐标（每个点坐标都有一个对应的二进位数字），y表示当前点下标
double ans = 1e9;//70000的原因：2的16次方不足70000
double dis[20][20] = { 0 };
#define s(n)  ((n)*(n))
void dfs4(int t, int now, double s)
{
	if (t == 0)
	{
		ans = min(ans, s);
		return;
	}
	for (int k = t;k;k -= (k & (-k)))
	{
		int j = ind[k & (-k)], temp = t - (1 << j);
		if (dp[temp][j] != 0 && dp[temp][j] <= s + dis[now][j]) continue;
		if (s + dis[now][j] >= ans)continue;
		dfs4(temp, j, dis[now][j] + s);
	}
}
int main5()
{
	int n;
	cin >> n;
	p[0].x = p[0].y = 0;
	for (int i = 1;i <= n;i++)
	{
		cin >> p[i].x >> p[i].y;
	}
	for (int i = 0, k = 1;i <= n;k *= 2,i++)ind[k] = i;
	for (int i = 0;i <= n;i++)
	{
		for (int j = i+1;j <= n;j++)
		{
			dis[j][i]=dis[i][j] = sqrt(s(p[i].x - p[j].x) + s(p[i].y - p[j].y));
		}
	}
	dfs4((1 << (n + 1)) - 2,0 , 0);
	printf("%.2llf", ans);
	return 0;
}