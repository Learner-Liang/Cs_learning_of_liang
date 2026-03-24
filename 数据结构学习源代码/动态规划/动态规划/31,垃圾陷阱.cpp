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
                cout << arr[i].t;
                return 0;
            }
            dp[j + arr[i].f] = max(dp[j],  dp[j+arr[i].f]);//³Ô
            dp[j] += arr[i].h;//µþ
        }
        if(Max>=arr[i].t)
        Max += arr[i].f;
    }
    cout << Max;
    return 0;
}
