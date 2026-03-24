#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main3()
{
	//f[i][j]将数字划分为j份
	//分为有1部分和无1部分，无1部分每一个值大于1，每个元素减去1也是合法的
	//f[i][j]=f[i-1][j-1]+f[i-j][j]
	int n, k;
	cin >> n >> k;
	int arr[205][8] = { 0 };
	for (int i = 1;i <= k;i++)arr[i][i] = 1;
	for (int i = 1;i <= n;i++)arr[i][1] = 1;
	for (int i = 2;i <= n;i++)
	{
		for (int j = 2;j <=min(i,k);j++)
		{
			if (i <= j)continue;
			arr[i][j] = arr[i - 1][j - 1];
			arr[i][j] += arr[i - j][j];
		}
	}
	cout << arr[n][k];
	return 0;
}