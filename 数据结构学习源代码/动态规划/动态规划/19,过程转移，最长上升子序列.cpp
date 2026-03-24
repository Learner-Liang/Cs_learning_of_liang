#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int binary_search(vector<int>& len, int n, int x)
{
	int head = 0,tail = n, mid;
	while (head < tail)
	{
		mid = (head + tail + 1) >> 1;
		if (len[mid] < x)head = mid;
		else
			tail = mid - 1;
	}
	return head;
}
int main19()
{
	//dp[i]表示以i位置为结尾的最长长度
	//len[j]表示长度为j的序列最后一位最小值,len数组是单增的，因而可以使用二分法
	int n;
	cin >> n;
	vector<int>dp(1000005, 1), len(1000005, 0x3f3f3f3f), a(1000005);
	for (int i = 1, k;i <= n;i++)

	{
		scanf("%d", &k);
		a[i] = k;
	}
	/*int ans = 0;
	len[1] = a[1];
	for (int i = 1;i <= n;i++)
	{
		for (int j = i - 1;j > 0;j--)
		{
			if (a[i] > len[j])
			{
				dp[i] = j + 1;
				ans = max(ans, j + 1);
				len[dp[i]] = min(a[i], len[dp[i]]);
				break;
			}
		}
		len[1] = min(len[1], a[i]);
	}
	cout << ans;*/
	len[0] = -1;
	int ans = 0;
	for (int i = 1;i <= n;i++)
	{
		dp[i] = binary_search(len,ans,a[i]) + 1;
		len[dp[i]] = a[i];
		if (dp[i] > ans)ans = dp[i];
	}
	cout << ans;
	return 0;
}