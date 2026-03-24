/*给定一个n个节点m条边的带权有向图G，节点编号从1到n，
保证输入的图中没有重边和自环。
你可以在图中添加不超过k条权值为0的有向边，添加之后允许有重边和自环，
不过这些边的起点和终点的编号差不能超过1。
现在，你要想办法使得节点1到节点n的最短路径的权值尽可能小，输出这个最小的权值。*/
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
            d[j][i] = d[j][i - 1]; // 这一层的基础是上一层
            if (j > 1) d[j][i] = min(d[j][i], d[j - 1][i - 1]); // 从左边传过来
            if (j < n) d[j][i] = min(d[j][i], d[j + 1][i - 1]); // 【补全】从右边传过来
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
    return 0;

}
