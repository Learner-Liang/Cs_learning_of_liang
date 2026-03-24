/*
【题目】7 树的重心
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
using namespace std;
bool st[1000] = { 0 };
vector<int>h[1000];
int n,m;
int ans = 0;

int dfs(int root) {
	st[root] = 1;
	int res = 0, sum = 1;
	for (int i = 0, I = h[root].size();i < I;i++) {
		if (st[h[root][i]])continue;
		int s = dfs(h[root][i]);
		res = max(res, s);
		sum += s;
	}
	res = max(res, n - res);
	ans = max(res, ans);
	return sum;
}
int main() {
	cin >> n >> m;
	for (int i = 0, a, b;i < m;i++) {
		cin >> a >> b;
		h[a].push_back(b);
		h[b].push_back(a);
	}
	dfs(1);
	cout << ans;
	return 0;
}