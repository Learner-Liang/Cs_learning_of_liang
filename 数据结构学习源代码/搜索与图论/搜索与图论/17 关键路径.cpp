#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>
#include <cstring>
using namespace std;

typedef struct edge {
    int to, val;
}edge;
int n, m;
const int MAXN = 10005;
const int INF = 0x3f3f3f3f;
int e[MAXN] = { 0 }, l[MAXN];

vector<edge>h[MAXN], dh[MAXN];
int debug[MAXN] = { 0 };
int sort_line[MAXN];

int cnt = 0;


int deadline;

void dfs(int* output, int root, int num) {
    if (l[root] != e[root]) {
        return;
    }
    output[num] = root;
    if (root == n) {
        for (int i = 0;i <= num;i++)cout << output[i] << " ";
        cout << endl;
        return;
    }
    for (int i = 0, I = h[root].size();i < I;i++) {
        //l[i]==e[i]表明i是关键节点，但不一定是当关键路径的关键节点
        if (h[root][i].val + e[root] == l[h[root][i].to])dfs(output, h[root][i].to, num + 1);
    }
    return;
}
int key_way() {
    queue<int>q;
    for (int i = 1;i <= n;i++) {
        if (debug[i] == 0) {
            q.push(i);
            sort_line[cnt++] = i;
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0, I = h[cur].size();i < I;i++) {
            debug[h[cur][i].to] -= 1;
            if (debug[h[cur][i].to] == 0) {
                sort_line[cnt++] = h[cur][i].to;
                q.push(h[cur][i].to);
            }
            e[h[cur][i].to] = max(e[h[cur][i].to], e[cur] + h[cur][i].val);
        }
    }
    deadline = e[n]; // 假设 n 是唯一的汇点
    for (int i = 1; i <= n; i++) l[i] = deadline;

    for (int i = cnt - 1;i >= 0;i--) {
        for (int j = 0, J = dh[sort_line[i]].size();j < J;j++) {
            l[dh[sort_line[i]][j].to] = min(l[dh[sort_line[i]][j].to],
                l[sort_line[i]] - dh[sort_line[i]][j].val);
        }
    }

    //cout<<l[4]<<" "<<e[4]<<endl;
    int output[MAXN];
    dfs(output, 1, 0);
    return 0;

}
int main() {
    cin >> n >> m;
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        h[a].push_back(edge{ b,c });
        dh[b].push_back({ a,c });
        debug[b] += 1;
    }
    key_way();
    return 0;
}
/*
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stack>

using namespace std;

const int MAXN = 10005;
const int INF = 0x3f3f3f3f;

struct Edge {
    int to;
    int weight;
};

// 邻接表
vector<Edge> adj[MAXN];
// 逆邻接表 (用于求vl，或者直接用拓扑序列逆序更新也可以，这里用拓扑序列逆序更方便)
int in_degree[MAXN];
int ve[MAXN]; // 最早开始时间
int vl[MAXN]; // 最迟开始时间
int n, m;

// 用于DFS打印路径
vector<int> path;

// 比较函数，用于对邻接表排序，保证输出顺序
bool compareEdges(const Edge& a, const Edge& b) {
    return a.to < b.to;
}

void dfs(int u) {
    path.push_back(u);

    // 如果到达汇点，打印当前路径
    if (u == n) {
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        // 遍历所有邻接点
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            // 关键判断：只有当这条边是关键边时才走
            // 判定条件：起点最早时间 + 耗时 == 终点最迟时间
            // 这意味着这条边没有任何“机动时间”
            if (ve[u] + w == vl[v]) {
                dfs(v);
            }
        }
    }

    // 回溯
    path.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        in_degree[v]++;
    }

    // 预处理：对邻接表排序，确保DFS时优先访问编号小的节点
    // 这样才能保证输出顺序是符合预期的（如 1 2 5 7 9 在 1 2 5 8 9 之前）
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end(), compareEdges);
    }

    // --- 1. 拓扑排序 求 ve ---
    queue<int> q;
    vector<int> topo_order;
    fill(ve, ve + n + 1, 0);

    // 题目默认1是源点，但为了保险把所有入度为0的都加进去
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            if (ve[u] + w > ve[v]) {
                ve[v] = ve[u] + w;
            }
            in_degree[v]--;
            if (in_degree[v] == 0) q.push(v);
        }
    }

    // --- 2. 逆向 求 vl ---
    fill(vl, vl + n + 1, INF);
    // 汇点的最迟时间 = 汇点的最早时间
    vl[n] = ve[n];

    // 逆拓扑序遍历
    for (int i = topo_order.size() - 1; i >= 0; i--) {
        int u = topo_order[i];
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;
            // vl[u] = min(vl[v] - w)
            if (vl[v] - w < vl[u]) {
                vl[u] = vl[v] - w;
            }
        }
    }

    // --- 3. DFS 输出所有路径 ---
    // 从源点1开始搜索
    dfs(1);

    return 0;
}
 */