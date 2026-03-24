//方向数组
#include <iostream>
using namespace std;
int dir1[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
//坐标合法判断：在最外层放一层障碍
int vis[12][12] = { 0 };
int ans = 0;
void dfs2(int sx,int sy,int fx,int fy)
{
	if (sx == fx && sy == fy)
	{
		ans += 1;
		return;
	}
	vis[sx][sy] = 0;
	for (int i = 0;i < 4;i++)
	{
		int dx = sx + dir1[i][0], dy = sy + dir1[i][1];
		if (vis[dx][dy])
		{
			dfs2(dx, dy, fx, fy);
		}
	}
	vis[sx][sy] = 1;
}
int main4()
{
	int n, m, t;
	cin >> n >> m >> t;
	int sx, sy, fx, fy;
	cin >> sx >> sy >> fx >> fy;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
			vis[i][j] = 1;
	}
	for (int i = 0, a, b;i < t;i++)
	{
		cin >> a >> b;
		vis[a][b] = 0;
	}
	dfs2(sx, sy, fx, fy);
	printf("%d", ans);
	return 0;
}