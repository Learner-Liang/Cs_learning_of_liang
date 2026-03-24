#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
using namespace std;
struct group
{
	int a, b;//重量与i价值
};
void getDP(map<int, vector<group>>arr, int* dp,int m);
int main11()
{
	int m, n;
	cin >> m >> n;
	map<int, vector<group>>arr;
	int dp[1000] = { 0 };
	for (int i = 0, a, b, c;i < n;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		group g = { a,b };
		arr[c].push_back(g);
	}
	getDP(arr, dp, m);
	cout << dp[m];
	return 0;
}
void getDP(map<int, vector<group>>arr, int* dp,int m)
{
	int n = arr.size();
	for (int i = 1;i <= n;i++)
	{
		int num = arr[i].size();
		for (int j = m;j;j--)
		{
			for (int k = 0;k < num;k++)
			{
				if (j < arr[i][k].a)continue;
				dp[j] = max(dp[j], dp[j - arr[i][k].a] + arr[i][k].b);
			}
		}
	}
}