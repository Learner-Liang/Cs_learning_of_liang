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