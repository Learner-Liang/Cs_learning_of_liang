/*
【题目】11 查找文献 求字典树最小序列
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

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int n, m;
vector<int>edge[100005];
bool b[100005] = { 0 };
void dfs(int root) {
	cout << root << " ";
	for (int i = 0, I = edge[root].size();i < I;i++) {
		if (b[edge[root][i]])continue;
		b[edge[root][i]] = 1;
		dfs(edge[root][i]);
	}
	return;
}
void bfs(int root) {
	queue<int>q;
	q.push(root);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		cout << cur << " ";
		for (int i = 0, I = edge[cur].size();i < I;i++) {
			if (b[edge[cur][i]])continue;
			b[edge[cur][i]] = 1;
			q.push(edge[cur][i]);
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	for (int i = 0, a, b;i < m;i++) {
		cin >> a >> b;
		edge[a].push_back(b);
	}
	for (int i = 1;i <= n;i++)sort(edge[i].begin(), edge[i].end());
	b[1] = 1;
	dfs(1);
	for (int i = 1;i <= n;i++)b[i] = 0;
	cout << endl;
	b[1] = 1;
	bfs(1);
	return 0;
}