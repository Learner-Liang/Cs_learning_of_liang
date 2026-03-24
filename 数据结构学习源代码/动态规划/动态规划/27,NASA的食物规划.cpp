#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;
int main27()
{
	//双条件01背包

	//刷表法
	int H, T;
	cin >> H >> T;
	int n;
	cin >> n;
	int dp[405][405] = { 0 };
	for (int i = 1,h,t,k;i <= n;i++)
	{
		cin >> h>> t>> k;
		for (int x =H;x >=h;x--)
		{
			
			for (int y = T;y >= t;y--)
			{
				dp[x][y] = max(dp[x][y], dp[x - h][y - t]+k);
			}
		}
	}
	cout << dp[H][T];
	return 0;
}