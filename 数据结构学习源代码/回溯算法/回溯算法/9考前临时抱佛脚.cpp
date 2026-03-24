#include <iostream>
#include <cstdlib>
using namespace std;
int arr2[4][25] = { 0 };
int s[4];
int ans4 = 0;
int dis3[4] = { 0 };
void dfs9( int i, int sum, int num,int p)//要时刻记住用树
{
	if (num == 0)
	{
		ans4 = min(ans4, abs(dis3[i] - sum * 2));
		return;
	}
	for (int k = 1;k <= num;k++)
	{
		if(k)
		for (int j = p;j < s[i];j++)
		{
			dfs9( i, sum + arr2[i][j], k-1,j+1);
		}
	}
}
//void dfs9(int x, int l, int r, int k)
//{
//	if (k == s[x])
//	{
//		ans4 = min(ans4, max(l, r));
//		return;
//	}
//	l += arr2[x][k];
//	dfs9(x, l, r, k + 1);
//	l -= arr2[x][k];
//	r += arr2[x][k];
//	dfs9(x, l, r, k + 1);
//	r -= arr2[x][k];
//}
int main()
{
	for (int i = 0;i < 4;i++)
	{
		cin >> s[i];
	}
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < s[i];j++)
		{
			cin >> arr2[i][j];
			dis3[i] += arr2[i][j];
		}
	}
	int all = 0;
	for (int i = 0;i < 4;i++)
	{
		ans4 = 10000;
		dfs9(i,0,s[i]/2,0);
		all += (dis3[i] + ans4) / 2;
		//cout << all << endl;
	}
	cout << all;
	/*for (int i = 0;i < 4;i++)
	{
		cin >> s[i];
	}
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < s[i];j++)
		{
			cin >> arr2[i][j];
		}
	}
	int all = 0;
	for (int i = 0;i < 4;i++)
	{
		ans4 = 10000;
		dfs9(i, 0, 0, 0);
		all += ans4;
	}
	cout << all;*/
	return 0;
}
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
#include <unordered_map>
using namespace std;

#define MAX_N 20
#define MAX_NUM 9999999
int s[10], sum[10] = { 0 };
int t[10][MAX_N + 5];
unordered_map<int, int> ind;

int solve(int k) {
	int ans = MAX_NUM;
	int T = (1 << s[k]);
	for (int i = 0; i < T; i++) {
		int j = i, l = 0, r = 0;
		while (j) {
			l += t[k][ind[j & -j]];
			j -= (j & -j);
		}
		r = sum[k] - l;
		ans = min(ans, max(l, r));
	}
	return ans;
}

int main() {
	for (int i = 0; i < 4; i++) cin >> s[i];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < s[i]; j++) {
			cin >> t[i][j];
			sum[i] += t[i][j];
		}
	}
	for (int k = 1, i = 0; i <= MAX_N; i++, k *= 2) ind[k] = i;
	int ans = 0;
	for (int i = 0; i < 4; i++) {
		ans += solve(i);
	}
	cout << ans << endl;
	return 0;
}
