/*
【题目】31,垃圾陷阱
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

#define MAX_N 100
struct Data {
    int t, f, h;
} arr[MAX_N + 5];
int dp[2 * MAX_N + 5] = { 0 };

bool cmp(const Data& a, const Data& b) {
    return a.t < b.t;
}

int main31() {
    int D, G;
    cin >> D >> G;
    for (int i = 0; i < G; i++) {
        cin >> arr[i].t >> arr[i].f >> arr[i].h;
    }
    sort(arr, arr + G, cmp);
   /* dp[0] = 10;
    for (int i = 0; i < G; i++) {
        for (int j = D; j >= 0; j--) {
            if (dp[j] < arr[i].t) continue;
            if (j + arr[i].h >= D) {
                cout << arr[i].t << endl;
                return 0;
            }
            dp[j + arr[i].h] = max(dp[j + arr[i].h], dp[j]);
            dp[j] += arr[i].f;
        }
    }*/
   // cout << dp[0] << endl;
    int Max = 10;
    //dp[10] = arr[0].h;
    for (int i = 0;i < G;i++)
    {
        for (int j =Max;j >= 10;j--)
        {
            if (j < arr[i].t)break;
            if (dp[j] + arr[i].h >= D)
            {
                // 步骤1（代码实现）：读取输入并完成必要初始化。
                // 目的：把原始输入转化为程序可处理的数据状态。
                // 实现：通过输入语句与初始赋值准备基础变量。
                // 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
                // 目的：为核心转移/搜索/计算过程提供载体。
                // 实现：用数组、容器或自定义结构存储中间状态与关系。
                // 步骤3（代码实现）：执行核心算法流程。
                // 目的：按照题意完成状态转移、搜索或计算求解。
                // 实现：通过循环、递归或转移方程推进计算直到得到答案。

                cout << arr[i].t;

                // 步骤4（代码实现）：输出结果并返回。
                // 目的：给出最终答案并结束程序执行。
                // 实现：调用输出语句打印结果，并通过 return 结束流程。
                return 0;
            }
            dp[j + arr[i].f] = max(dp[j],  dp[j+arr[i].f]);//
            dp[j] += arr[i].h;//
        }
        if(Max>=arr[i].t)
        Max += arr[i].f;
    }
    cout << Max;
    return 0;
}
