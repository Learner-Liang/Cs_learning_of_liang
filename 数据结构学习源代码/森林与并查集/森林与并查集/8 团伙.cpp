#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
using namespace std;
//p 1892
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> fa(2 * n + 1);  // 并查集数组 (1..2n)
    for (int i = 1; i <= 2 * n; i++) {
        fa[i] = i;  // 初始化
    }

    // 路径压缩的查找
    function<int(int)> find = [&](int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);  // 路径压缩
        }
        return fa[x];
        };

    // 合并操作
    auto merge = [&](int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            fa[rx] = ry;
        }
        };

    // 处理关系
    for (int i = 0; i < m; i++) {
        char opt;
        int a, b;
        cin >> opt >> a >> b;
        if (opt == 'F') {
            merge(a, b);          // 朋友域合并
            merge(a + n, b + n);  // 敌人域合并
        }
        else {
            merge(a, b + n);  // a的朋友域与b的敌人域合并
            merge(b, a + n);  // b的朋友域与a的敌人域合并
        }
    }

    // 统计朋友域的连通分量（团体数）
    unordered_set<int> roots;
    for (int i = 1; i <= n; i++) {
        roots.insert(find(i));  // 插入根节点
    }
    cout << roots.size() << endl;

    return 0;
}