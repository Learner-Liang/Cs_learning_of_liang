/*
种新型的激光炸弹，可以摧毁一个边长为 R 的正方形内的所有的目标。
现在地图上有 N(N≤10000) 个目标，用整数 Xi,Yi(其值在[0,5000]) 表示目标在地图上的位置，每个目标都有一个价值 Wi。
​ 激光炸弹的投放是通过卫星定位的，但其有一个缺点，就是其爆破范围，即那个边长为 R 的正方形的边必须和 x,y 轴平行。
若目标位于爆破正方形的边上，该目标将不会被摧毁。求一颗炸弹最多能炸掉地图上总价值为多少的目标。

*/
#include <iostream>
using namespace std;
int main4()
{
	int n, r;
	cin >> n >> r;
	int s[55][55] = { 0 };
	int max_x = r,max_y = r;//初始化为r，否则在计算前缀和阶段，可能到不了r，导致r正方形为0
	for (int i = 0,x,y,w;i < n;i++)
	{
		cin >> x >> y >> w;
		s[x + 1][y + 1] = w;
		//确定循环遍历范围
		if (x + 1 > max_x)max_x = x + 1;
		if (y + 1 > max_y)max_y = y + 1;
	}
	int ans = 0;
	for (int i = 1;i <= max_x;i++)
	{
		for (int j = 1;j <= max_y;j++)
		{
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	}
	int limit_x = max_x - r, limit_y = max_y - r;
	for (int x = 0;x <= limit_x;x++)
	{
		for (int y = 0;y <= limit_y;y++)
		{
			ans = max(ans, s[x][y]+s[x - r][y - r]-s[x-r][y]-s[x][y-r]);
		}
	}
	cout << ans;
	return 0;
}