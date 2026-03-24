//优化：方向数组
#include <iostream>
#include <queue>
using namespace std;
int dis[405][405] = {0};
int dir[8][2] = { {2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2} };
void dfs1(int count, int x, int y,int n,int m)
{
	if (dis[x][y] <= count)return;
	dis[x][y] = count;
	for (int i = 0;i < 8;i++)
	{
		int dx = x + dir[i][0], dy = y + dir[i][1];
		if (dx <= n && dx > 0 && dy <= m && dy > 0)
			dfs1(count + 1, dx, dy, n, m);
	}
}
//层序遍历：后面到达的点一定不如以前出现的次数：适合求解最短步长
//用队列
typedef struct Node
{
	Node(int x, int y, int s) :x(x), y(y), s(s) {};
	int x, y, s;
}Node;
void bfs(int x,int y,int n,int m)//由于深度优先遍历不涉及比较，因而直接赋值为-1就可以了
{
	queue<Node>q;
	q.push(Node(x, y, 0));
	dis[x][y] = 0;
	while (!q.empty())
	{
		Node now = q.front();
		q.pop();
		for (int i = 0;i < 8;i++)
		{
			int dx = now.x + dir[i][0], dy = now.y + dir[i][1];
			if (dx <= n && dx > 0 && dy <= m && dy > 0&&dis[dx][dy]==500)
			{
				q.push(Node(dx, dy, now.s+1));
				dis[dx][dy] = now.s + 1;;
			}
		}
	}
}
int main3()
{
	int n, m, x, y;
	cin >> n >> m >> x >> y;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			dis[i][j] = 500;
		}
	}
	/*dfs1(0, x, y, n, m);*/
	bfs(x, y, n, m);
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
		{
			if (dis[i][j] == 500)
			{
				printf("-1 ");
					continue;
			}
			printf("%d ", dis[i][j]);
		}
		printf("\n");
	}
	return 0;
}