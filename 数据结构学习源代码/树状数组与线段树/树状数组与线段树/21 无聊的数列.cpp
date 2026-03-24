/*
【题目】21 无聊的数列
【整体算法思路】
步骤1：读取输入并完成初始化。先把题目给的数字/字符串准确放进变量。
目的：只有输入含义搞清楚，后面 for/while 的边界与数组下标才不会写错。
步骤2：建立数据结构/状态定义（尤其是 DP 的 dp[i][j] 到底表示什么）。
目的：把“题目文字”翻译成“程序状态”；定义不清，转移方程一定写不对。
步骤3：执行核心算法（循环/递归/搜索/转移），把子问题答案逐步合成总答案。
目的：每一轮循环都要回答“我现在在解决哪个子问题，为什么这样更新是正确的”。
步骤4：输出结果并结束程序。输出下标必须和状态定义一一对应。
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
    // 步骤3细化（判断条件解释）：这个 if/while 是“题目约束”的程序化表达，用来过滤非法状态。
    // 为什么这么写：若不先判断就更新，常见后果是越界、重复使用元素或把不可能状态算进去。

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
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行更新，把“已知子问题”推到“当前问题”。
// 目的：让小问题先解、大问题后解；若是 DP，要先说清状态定义，再写状态转移方程。
// 关键代码说明：max/min/松弛语句对应数学关系；循环顺序和 if 条件共同保证“不会漏解、不会重算、不会越界”。

    
    // 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
    // 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
    cin >> n >> m;
    
    // 步骤3细化（核心循环解释）：for/while 的顺序不是随便写的，它决定“先用哪些已知结果”。
    // 顺序背后的原理：0/1 背包常用倒序防止同一物品被重复选；图最短路按当前最优点扩展才满足贪心前提。
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