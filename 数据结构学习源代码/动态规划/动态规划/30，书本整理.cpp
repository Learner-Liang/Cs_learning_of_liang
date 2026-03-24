#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
struct book
{
	int h, w;
};
int main30()
{
	int n, k;
	cin >> n >> k;
	//dp[i][k]=min(dp[j][k-1]+w[i]-w[j])前i本书中选择k本。i必须选
	struct book books[105];
	int K = n - k;
	vector<vector<int>>dp(105,vector<int>(105,0x3f3f3f));
	for (int i = 1;i <= n;i++)
	{
		cin >> books[i].h >> books[i].w;
	}
	sort(books+1, books +1+ n, [&](const book& a, const book& b)->bool
		{
			return a.h < b.h;
		});
	int ans = 0x3f3f3f;
	for (int i = 1;i <= n;i++)
	{
		dp[i][0] = dp[i][1] = 0;
		for (int j = 2;j <= i;j++)
		{
			for (int x = j-1;x < i;x++)
				dp[i][j] = min(dp[i][j], dp[x][j - 1] + abs(books[i].w - books[x].w));
		}
		ans = min(ans, dp[i][K]);
	}
	cout << ans;
	return 0;
}