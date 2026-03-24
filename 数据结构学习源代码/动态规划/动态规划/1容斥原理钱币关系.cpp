#include <iostream>
#include <algorithm>
#include <vector>
//先不考虑重叠的情况，计数时候再把重复的数目排斥出去，少了就再加
//f[i][j]用前i种货币，凑足j元的中数
//f[i][j]=f[i][j-a[i]]+f[i-1][j]
using namespace std;
int main1()
{
	int a[25] = { 0 }, f[25][10005] = { 0 };
	int m , n ;
	m = 10;
	cin >> m >> n;
	for (int i = 1;i <= m;i++)
	{
		cin >> a[i];
	}
	for (int i = 1;i <= m;i++)
	{
		f[i][0] = 1;//由公式关系
		for (int j = 1;j <= n;j++)
		{
			f[i][j] = f[i - 1][j];
			if(j - a[i]>=0)
			f[i][j] += f[i][j - a[i]];
			f[i][j] %=  9973;
		}
	}
	cout << f[m][n];
	return 0;
}