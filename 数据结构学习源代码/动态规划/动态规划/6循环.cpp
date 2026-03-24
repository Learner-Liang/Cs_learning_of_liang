#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main6()
{
	int n, k, base = 0, x, y;
	cin >> n >> k;
	for (int i = 0;i < k;i++)base *= 10;
	//每次取最后一位
	x =n% base;
	y = x;
	int cnt = 1;
	while (x*y%base!= x)
	{
		y = x * y % base;
		cnt++;
	}
	cout << cnt;
	//也可以从每一位的角度考虑，每一位都会出现重复循环，求每一位出现重复循环的累乘之积即可
	//由个位的循环长度求十位，由十位求百位
	return 0;
}