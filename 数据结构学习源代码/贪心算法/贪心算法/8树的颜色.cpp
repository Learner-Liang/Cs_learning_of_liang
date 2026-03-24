/*
【题目】8树的颜色
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
int main()
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

	//ȾɫڵӽڵΪֵһһȾɫӽڵ

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
    using namespace std;

#define MAX_N 1000

    int C[MAX_N + 5] = { 0 };
    int fa[MAX_N + 5] = { 0 };
    int vis[MAX_N + 5] = { 0 };
    int cnt[MAX_N + 5] = { 0 };
    double w[MAX_N + 5] = { 0 };
    int n, r;
    long long ans = 0;

    int find_x() {
        int x = -1;
        for (int i = 1; i <= n; i++) {
            if (i == r || vis[i] == 1) continue;
            if (x == -1 || w[x] < w[i]) x = i;
        }
        return x;
    }

    int find_father(int x) {
        if (vis[fa[x]]) return find_father(fa[x]);
        return fa[x];
    }

    int main() {
        cin >> n >> r;
        for (int i = 1; i <= n; i++) {
            cin >> C[i];
            ans += C[i];
            fa[i] = i;
            w[i] = C[i];
            cnt[i] = 1;
        }
        for (int i = 1, a, b; i < n; i++) {
            cin >> a >> b;
            fa[b] = a;
        }
        for (int i = 1; i < n; i++) {
            int x = find_x();
            int father_x = find_father(x);
            ans += cnt[father_x] * C[x];
            C[father_x] += C[x];
            cnt[father_x] += cnt[x];
            w[father_x] = 1.0 * C[father_x] / cnt[father_x];
            vis[x] = 1;
        }
        cout << ans << endl;
        return 0;
    }


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}