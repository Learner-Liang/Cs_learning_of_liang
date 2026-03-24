/*
【题目】6挤奶
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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define MAX_N 50000

struct Data {
    int l, r, id;
} arr[MAX_N + 5];
int m_time[MAX_N + 5], ans[MAX_N + 5];
int cnt = 0;

bool cmp(const Data& a, const Data& b) {
    // 步骤1（代码实现）：读取输入并完成必要初始化。
    // 目的：把原始输入转化为程序可处理的数据状态。
    // 实现：通过输入语句与初始赋值准备基础变量。
    // 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
    // 目的：为核心转移/搜索/计算过程提供载体。
    // 实现：用数组、容器或自定义结构存储中间状态与关系。
    // 步骤3（代码实现）：执行核心算法流程。
    // 目的：按照题意完成状态转移、搜索或计算求解。
    // 实现：通过循环、递归或转移方程推进计算直到得到答案。
    
    if (a.l != b.l) return a.l < b.l;//sortȶ򷽷
    
    // 步骤4（代码实现）：输出结果并返回。
    // 目的：给出最终答案并结束程序执行。
    // 实现：调用输出语句打印结果，并通过 return 结束流程。
    return a.id < b.id;
}

int main6() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &arr[i].l, &arr[i].r);
        arr[i].id = i;
    }
    sort(arr, arr + n, cmp);
    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = 0; j < cnt; j++) {
            if (m_time[j] < arr[i].l) {
                pos = j;
                break;
            }
        }
        if (pos == -1) pos = (cnt++);
        m_time[pos] = arr[i].r;
        ans[arr[i].id] = pos + 1;
    }
    printf("%d\n", cnt);
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
