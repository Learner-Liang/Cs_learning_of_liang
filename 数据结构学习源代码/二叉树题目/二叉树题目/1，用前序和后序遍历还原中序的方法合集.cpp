/*
【题目】1，用前序和后序遍历还原中序的方法合集
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
#include <set>
#include <algorithm>
#include <string>
//#include <pair>
using namespace std;
string a, b;
int n = 0;
long long ans = 0;
int dfs(int l1, int r1, int l2, int r2)
{
    long long k = 0;
    if (r2 - l2 == 0)
    {
        if (b[r2] == a[l1])k += 1;
        return k;
    }
    if (r2 - l2 < 0)return 1;
    if (a[l1] == b[r2])
    {
        for (int i = l1;i <= r1;i++)
        {
            k += dfs(l1 + 1, i, l2, l2 + i - l1 - 1) * dfs(i + 1, r1, l2 + i - l1, r2 - 1);
        }
    }
    return k;
}
int main1()
{
    cin >> a >> b;
    n = a.size();
    cout << dfs(0, n - 1, 0, n - 1);
    return 0;
}