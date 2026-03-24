/*
【题目】15 最短路：spfa
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
#include <set>
using namespace std;
int n, m, root;
typedef pair<int, int> P;
vector<P>h[1000];
int d[1000];
bool st[1000] = { 0 };
void spfa() {
	memset(d, 0x3f, sizeof(d));
	d[root] = 0;
	queue<int>q;
	q.push(root);
	st[root] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		st[cur] = 0;
		for (int i = 0, I = h[cur].size();i < I;i++) {
			if (d[cur] + h[cur][i].second < d[h[cur][i].first]) {
				d[h[cur][i].first] = d[cur] + h[cur][i].second;
				if (st[h[cur][i].first] == 0)q.push(h[cur][i].first);
				st[h[cur][i].first] = 1;
			}
		}
	}
	return;
}

int main() {
	cin >> n >> m >> root;
	for (int i = 0, a, b, c;i < m;i++) {
		cin >> a >> b >> c;
		h[a].push_back(P{b,c});
	}
	return 0;
}