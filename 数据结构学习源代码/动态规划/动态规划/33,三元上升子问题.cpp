#define _CRT_SECURE_NO_WARNINGS
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
int main33()
{
	//f[i]是以i为结尾的三元上升子序列的数量
	//要得知以j为结尾的二元上升序列数量
	//改为二维，f[I][J][K]k表示维度
	int n;
	cin >> n;
	int f[30005] = { 0 }, a[30005] = { 0 };
	vector<int>count(30005, 0);
	int ans = 0;
	for (int i = 1;i <= n;i++)
	{
		scanf("%d", a + i);
		for (int j = i-1;j > 0;j--)
		{
			if (a[j] < a[i])count[i]++;
		}
		for (int j = i - 1;j > 1;j--)
			if (a[j] < a[i]) f[i] += count[j];
		ans += f[i];
	}
	cout << ans;
	return 0;
}