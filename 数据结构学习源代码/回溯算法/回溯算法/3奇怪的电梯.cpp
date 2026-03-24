//优化：历史答案剪枝：求步数最小，通过历史步数，超过当前历史最短步数时候停止
#include <iostream>
using namespace std;
int to[205] = { 0 };
int vis[205] = { 0 };//从起点到每一个点的最短距离
void dfs(int count, int a, int b, int k)
{
	if (vis[a] <= count)return;
	vis[a] = count;
	if (a + to[a] <= k)dfs(count + 1, a + to[a], b, k);
	if (a - to[a] > 0)dfs(count + 1, a - to[a], b, k);
}
;int main2()
{
	int n, a, b;
	cin >> n >> a >> b;
	for (int i =1 ;i <= n;i++)
	{
		scanf_s("%d", to + i);
		vis[i] = n + 1;
	}
	dfs(0, a, b, n);
	if (vis[b] == n + 1)printf("-1");
	else printf("%d", vis[b]);
	return 0;
}