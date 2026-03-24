/*
【题目】17 买票
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




	//和奶牛类似，x表示前面有几个比自己小
	/*有N个人排队，每一个人都有一个val来对应，每一个后来人都会插入当前队伍的某一个位置pos。要求把队伍最后的状态输出。
	 第一行一个整数N(1≤N≤200,000)，表示n个人，接下来n行，每行两个整数x和val(0≤x≤i−1，0≤val≤32767)，
	 表示一个标记为val的人，插入到排在第x位置的人的后面。*/
/*
#include <iostream>
using namespace std;

#define lowbit(x) (x & (-x))
int c[2000005], a[2000005], b[2000005];
int ans[2000005];
void add(int i, int v, int n) {
    while (i <= n) c[i] += v, i += lowbit(i);
    return ;
}
int query(int i) {
    if (i == 0) return 0;
    return c[i] + query(i - lowbit(i));
}

int binary_search(int x, int n) {
    int l = 1, r = n, mid;
    while (l < r) {
        mid = (l + r) / 2;
        if (query(mid) < x) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    for (int i = 1; i <= n; i++) {
        add(i, 1, n);
    }
    for (int i = n; i >= 1; i--) {
        int pos = binary_search(a[i] + 1, n);
        ans[pos] = b[i];
        add(pos, -1, n);
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1) cout << " ";
        cout << ans[i];
    }
    cout << endl;
    return 0;
}

*/