/*
【题目】2马的遍历
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

//Ż
#include <iostream>
#include <queue>
using namespace std;
int dis[405][405] = {0};
int dir[8][2] = { {2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2} };
void dfs1(int count, int x, int y,int n,int m)
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


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	if (dis[x][y] <= count)return;
	dis[x][y] = count;
	for (int i = 0;i < 8;i++)
	{
		int dx = x + dir[i][0], dy = y + dir[i][1];
		if (dx <= n && dx > 0 && dy <= m && dy > 0)
			dfs1(count + 1, dx, dy, n, m);
	}
}
//浽ĵһǰֵĴʺ̲
//ö
typedef struct Node
{
	Node(int x, int y, int s) :x(x), y(y), s(s) {};
	int x, y, s;
}Node;
void bfs(int x,int y,int n,int m)//ȱ漰ȽϣֱӸֵΪ-1Ϳ
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