#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main7()
{
	int n, m;
	cin >> n >> m;
	//int f[35][35][35] = { 0 };
	//f[1][1][m] = f[1][m][1] = 1;
	//for (int x = 1;x <= m;x++)
	//{
	//	f[1][x][x + 1] = f[1][x][x - 1] = 1;
	//	f[0][x][x] = 1;
	//}
	//for (int i = 1;i <= n;i++)
	//{
	//	for (int x = 1;x <= m;x++)
	//	{
	//		for (int y = 1;y <= m;y++)
	//		{
	//			if (x == m)
	//				f[i][x][y] = f[i - 1][1][y] + f[i - 1][x - 1][y];
	//			else if (x == 1)
	//				f[i][x][y] = f[i - 1][m][y] + f[i - 1][x + 1][y];
	//			else
	//			f[i][x][y] = f[i - 1][x+1][y]+f[i-1][x-1][y];
	//			f[i][y][x] = f[i][x][y];
	//		}
	//	}
	//}
	////二维数组就可以了
	//cout << f[n][1][1];
	int f[35][35] = { 0 };
	f[0][1] = 1;
	for (int i = 1;i <= n;i++)
	{
		for (int j = 2;j <= m;j++)
		{
			f[i][j] = f[i - 1][j + 1] + f[i - 1][j - 1];
		}
		f[i][1] = f[i - 1][m] + f[i - 1][2];
		f[i][m] = f[i - 1][1] + f[i - 1][m - 1];
	}
	return 0;
}