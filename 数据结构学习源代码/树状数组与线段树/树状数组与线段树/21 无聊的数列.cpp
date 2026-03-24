/*
【题目】21 无聊的数列
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

/*άһ a i?
 ֲ֧

1 l r K Dһȵ r?l+1 ĵȲУΪ KΪ DӦӵ [l,r] Χеÿһϡ
 a l=a l+K,a l+1=a l+1+K+Da r=a r+K+(r?l)D
2 pѯеĵ p ֵ a p*/
//p1438
// 
// 
//߶ά
//ĳ޸Ĳ


/*#include <iostream>
using namespace std;

#define MAX_N 100000
#define L(n) (tree[n].l)
#define R(n) (tree[n].r)
#define S(n) (tree[n].sum)
#define X(n) (tree[n].x)
#define C(n) (tree[n].cnt)
#define define_mid int mid = (l + r) >> 1

struct Node {
    int l, r;
    long long sum, x, cnt;
} tree[MAX_N * 2 + 5];
int root = 1, cnt = 1;

int n, m;
int num[MAX_N + 5];

void UP(int ind) {
    S(ind) = S(L(ind)) + S(R(ind));
    return ;
}

void DOWN(int ind) {
    if (X(ind) == 0) return ;
    // 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
    // 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

    X(L(ind)) += X(ind);
    X(R(ind)) += X(ind);
    S(L(ind)) += C(L(ind)) * X(ind);
    S(R(ind)) += C(R(ind)) * X(ind);
    X(ind) = 0;
    return ;
}

int build(int ind, int l, int r) {
    X(ind) = 0, C(ind) = (r - l + 1);
    if (l == r) {
        S(ind) = num[l] - num[l - 1];
        return ind;
    }
    define_mid;
    L(ind) = build(++cnt, l, mid);
    R(ind) = build(++cnt, mid + 1, r);
    UP(ind);
    return ind;
}

long long query(int ind, int l, int r, int x, int y) {
    if (x <= l && r <= y) {
        return S(ind);
    }
    DOWN(ind);
    define_mid;
    long long ans = 0;
    if (x <= mid) ans += query(L(ind), l, mid, x, y);
    if (mid < y) ans += query(R(ind), mid + 1, r, x, y);
    return ans;
}

void modify(int ind, int l, int r, int x, int y, long long k) {
    if (x > y || y < l || r < x) return ;
    if (x <= l && r <= y) {
        X(ind) += k;
        S(ind) += C(ind) * k;
        return ;
    }
    DOWN(ind);
    define_mid;
    if (x <= mid) modify(L(ind), l, mid, x, y, k);
    if (mid < y) modify(R(ind), mid + 1, r, x, y, k);
    UP(ind);
    return ;
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
    
    // 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
    // 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
    for (int i = 1; i <= n; i++) cin >> num[i];
    build(root, 1, n);
    for (int i = 1, op; i <= m; i++) {
        cin >> op;
        if (op == 1) {
            long long l, r, k, d;
            cin >> l >> r >> k >> d;
            modify(root, 1, n, l, l, k);
            modify(root, 1, n, l + 1, r, d);
            modify(root, 1, n, r + 1, r + 1, -(k + (r - l) * d));
        } else {
            int p;
            cin >> p;
            
            // 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
            cout << query(root, 1, n, 1, p) << endl;
        }
    }
    

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}
*/