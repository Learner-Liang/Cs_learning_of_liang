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
            cout << query(root, 1, n, 1, p) << endl;
        }
    }

    // 步骤4（代码实现）：输出结果并返回。
    // 目的：给出最终答案并结束程序执行。
    // 实现：调用输出语句打印结果，并通过 return 结束流程。
    return 0;
}
*/