/*维护一个数列 a i?
 ，支持两种操作：

1 l r K D：给出一个长度等于 r?l+1 的等差数列，首项为 K，公差为 D，并将它对应加到 [l,r] 范围中的每一个数上。
即：令 a l=a l+K,a l+1=a l+1+K+D…a r=a r+K+(r?l)×D。
2 p：询问序列的第 p 个数的值 a p。*/
//p1438
// 
// 
//用线段树维护差分数组
//改成三个区间修改操作


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
    return 0;
}
*/