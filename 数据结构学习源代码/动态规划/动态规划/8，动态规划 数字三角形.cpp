#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main8()
{
	//HZOJ 42
	int n;
	cin >> n;
	int num[1005][1005] = { 0 };
	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			cin >> num[i][j];
		}
	}
	//从下往上
	/*for (int i = n - 1;i >= 1;i--)
	{
		for (int j = 1;j <= i;j++)
		{
			num[i][j] += max(num[i + 1][j], num[i + 1][j + 1]);
		}
	}
	cout << num[1][1];*/
	//从上往下
	for (int i = 2;i <= n;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			num[i][j] += max(num[i - 1][j], num[i - 1][j + 1]);
		}
	}
	int Max = 0;
	for (int i = 1;i <= n;i++)
	{
		Max = max(Max, num[n][i]);
	}
	cout << Max;
	return 0;
}