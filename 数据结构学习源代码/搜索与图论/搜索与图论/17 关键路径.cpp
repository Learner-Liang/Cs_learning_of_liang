/*
【题目】17 关键路径
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
        //l[i]==e[i]iǹؼڵ㣬һǵؼ·Ĺؼڵ
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
    deadline = e[n]; //  n ΨһĻ
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
    // 步骤1（代码实现）：读取输入并完成必要初始化。
    // 目的：把原始输入转化为程序可处理的数据状态。
    // 实现：通过输入语句与初始赋值准备基础变量。
    // 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
    // 目的：为核心转移/搜索/计算过程提供载体。
    // 实现：用数组、容器或自定义结构存储中间状态与关系。
    // 步骤3（代码实现）：执行核心算法流程。
    // 目的：按照题意完成状态转移、搜索或计算求解。
    // 实现：通过循环、递归或转移方程推进计算直到得到答案。

    cin >> n >> m;
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        h[a].push_back(edge{ b,c });
        dh[b].push_back({ a,c });
        debug[b] += 1;
    }
    key_way();

    // 步骤4（代码实现）：输出结果并返回。
    // 目的：给出最终答案并结束程序执行。
    // 实现：调用输出语句打印结果，并通过 return 结束流程。
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

// ڽӱ
vector<Edge> adj[MAXN];
// ڽӱ (vlֱҲԣ)
int in_degree[MAXN];
int ve[MAXN]; // 翪ʼʱ
int vl[MAXN]; // ٿʼʱ
int n, m;

// DFSӡ·
vector<int> path;

// ȽϺڶڽӱ򣬱֤˳
bool compareEdges(const Edge& a, const Edge& b) {
    return a.to < b.to;
}

void dfs(int u) {
    path.push_back(u);

    // 㣬ӡǰ·
    if (u == n) {
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        // ڽӵ
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int w = edge.weight;

            // ؼжϣֻеǹؼʱ
            // жʱ + ʱ == յʱ
            // ζûκΡʱ䡱
            if (ve[u] + w == vl[v]) {
                dfs(v);
            }
        }
    }

    // 
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

    // ԤڽӱȷDFSʱȷʱСĽڵ
    // ܱ֤˳ǷԤڵģ 1 2 5 7 9  1 2 5 8 9 ֮ǰ
    for (int i = 1; i <= n; ++i) {
        sort(adj[i].begin(), adj[i].end(), compareEdges);
    }

    // --- 1.   ve ---
    queue<int> q;
    vector<int> topo_order;
    fill(ve, ve + n + 1, 0);

    // ĿĬ1Դ㣬Ϊ˱հΪ0Ķӽȥ
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

    // --- 2.   vl ---
    fill(vl, vl + n + 1, INF);
    // ʱ = ʱ
    vl[n] = ve[n];

    // 
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

    // --- 3. DFS · ---
    // Դ1ʼ
    dfs(1);

    return 0;
}
 */