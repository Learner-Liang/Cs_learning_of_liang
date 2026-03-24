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
        
        // 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
        // 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
        
        // 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
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
            
            // 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
            // 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。
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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

    
    // 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
    // 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
    cin >> n >> m;
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        h[a].push_back(edge{ b,c });
        dh[b].push_back({ a,c });
        debug[b] += 1;
    }
    key_way();
    

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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