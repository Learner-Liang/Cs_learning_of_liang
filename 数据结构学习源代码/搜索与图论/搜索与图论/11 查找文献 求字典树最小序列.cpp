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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

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

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}