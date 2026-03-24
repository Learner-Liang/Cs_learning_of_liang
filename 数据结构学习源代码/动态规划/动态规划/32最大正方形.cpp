/*
【题目】32最大正方形
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

#define MAX_N 1500
int dp[MAX_N + 5][MAX_N + 5][2];

int main32() {
    int n, m, ans = 0;
    scanf_s("%d%d", &n, &m);
    for (int i = 1, a; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf_s("%d", &a);
            dp[i][j][1 - a] = 0;
            dp[i][j][a] = min(
                dp[i - 1][j - 1][a], min(
                    dp[i - 1][j][1 - a],
                    dp[i][j - 1][1 - a]
                )) + 1;
            ans = max(ans, dp[i][j][a]);
        }
    }
    cout << ans << endl;
    return 0;
}
