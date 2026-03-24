#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main12()
{
	//子序列就是相对顺序不变的序列
	//d[i]表示以i位为结尾的最长子序列长度
	//d[i]=max{d[j]}+1,j属于1到i-1
	int n;
	cin >> n;
	int a[1000005] = { 0 };
	int d[1000005] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		scanf_s("%d", a + i);
		d[i] = 1;
		int ans = 0;
		for (int j = 1;j < i;j++)
		{
			if (a[j] < a[i])
				ans = max(ans, d[j]);
		}
		d[i] += ans;
	}
	cout << a[n];
	return 0;
}