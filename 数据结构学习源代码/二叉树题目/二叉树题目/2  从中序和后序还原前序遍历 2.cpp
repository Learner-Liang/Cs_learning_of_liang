#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
//#include <pair>
using namespace std;
string a, b;//zhong  hou 
int n = 0;
string ans;
void dfs(int l1, int r1, int l2, int r2)
{
    if (r2 == l2)
    {
        ans += a[r1];
        return;
    }
    if (r2 < l2)return;
    int k = l1;
    while (a[k] != b[r2])k++;
    ans += a[k];
    dfs(l1, k - 1, l2, l2 + k - l1 - 1);
    dfs(k + 1, r1, l2 + k - l1, r2 - 1);
    return;
}
int main()
{
    cin >> a >> b;
    n = a.size();
    dfs(0, n - 1, 0, n - 1);
    cout << ans;
    return 0;
}