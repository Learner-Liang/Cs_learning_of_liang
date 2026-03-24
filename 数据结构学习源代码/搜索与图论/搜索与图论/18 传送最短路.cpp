/*
【题目】18 传送最短路
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

/*һnڵmߵĴȨͼGڵŴ1n
֤ͼûرߺԻ
ͼӲkȨֵΪ0ߣ֮رߺԻ
ЩߵյıŲܳ1
ڣҪ취ʹýڵ1ڵn·ȨֵССȨֵ*/
#include <iostream>
#include <vector>
using namespace std;
const long long INF = 0x3f3f3f3f3f3f3f3f;
int n, m, k;
long long g[1005][1005];
bool st[1005][11] = { 0 };
long long d[1005][11];
void dijstal() {
    d[1][0] = 0;
    for (int i = 0;i < n;i++) {
        int t = -1;
        for (int j = 1;j <= n;j++) {
            if (st[j][0] == 0 && (t == -1 || d[t][0] > d[j][0]))t = j;
        }
        st[t][0] = 1;
        for (int j = 1;j <= n;j++) {
            if (g[t][j] != INF) {
                d[j][0] = min(d[j][0], d[t][0] + g[t][j]);
            }
        }
    }
    for (int i = 1;i <= k;i++) {
        d[1][i] = 0;
        for (int j = 1; j <= n; j++) {
            d[j][i] = d[j][i - 1]; // һĻһ
            if (j > 1) d[j][i] = min(d[j][i], d[j - 1][i - 1]); // ߴ
            if (j < n) d[j][i] = min(d[j][i], d[j + 1][i - 1]); // ȫұߴ
        }
        for (int j = 1;j < n;j++) {
            int t = -1;
            for (int z = 1;z <= n;z++) {
                if (st[z][i] == 0 && (t == -1 || d[z][i] < d[t][i]))t = z;
            }
            st[t][i] = 1;
            for (int z = 1;z <= n;z++) {
                d[z][i] = min(d[z][i], d[t][i] + g[t][z]);
            }
        }

    }
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

    cin >> n >> m >> k;
    for (int i = 1;i <= n;i++) {
        for (int j = 0;j <= k;j++)d[i][j] = 0x3f3f3f3f3f3f3f3f;
        for (int j = 1;j <= i;j++)g[i][j] = g[j][i] = 0x3f3f3f3f3f3f3f3f;
    }
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        g[a][b] = c;
    }
    dijstal();
    if (d[n][k] == 0x3f3f3f3f3f3f3f3f)cout << -1;
    else cout << d[n][k];

    // 步骤4（代码实现）：输出结果并返回。
    // 目的：给出最终答案并结束程序执行。
    // 实现：调用输出语句打印结果，并通过 return 结束流程。
    return 0;

}
