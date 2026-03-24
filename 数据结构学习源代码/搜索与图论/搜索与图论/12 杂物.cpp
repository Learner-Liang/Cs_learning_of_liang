/*
【题目】12 杂物
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
int main() {
	int n;
	cin >> n;
	int ans = 0;
	vector<int>t(n + 1,0);
	for (int i = 1, len;i <= n;i++) {
		cin >> i >> len;
		int j;
		while (cin >> j && j) {
			t[i] = max(t[i], t[j]);
		}
		t[i] += len;
		ans = max(ans, t[i]);
	}
	cout << ans;
	return 0;
}