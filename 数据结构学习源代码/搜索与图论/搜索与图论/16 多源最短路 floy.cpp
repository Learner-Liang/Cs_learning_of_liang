/*
【题目】16 多源最短路 floy
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

using namespace std;
const long long NIF = 0x3f3f3f3f3f3f3f3f;
long long d[205][205], n, m;
void floy() {
    for (int k = 1;k <= n;k++) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            if (i == j)d[i][j] = 0;
            else d[i][j] =NIF;
        }
    }
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        d[a][b] = c;
    }
    floy();
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            if (d[i][j] == NIF)cout << -1 << " ";
            else cout << d[i][j] << " ";
        }
        cout << endl;
    }
}