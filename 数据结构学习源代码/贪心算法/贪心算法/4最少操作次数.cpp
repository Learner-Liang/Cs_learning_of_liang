#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main4()
{
	//HZOJ 511
	int a, b, k, ans = 0;
	cin >> a >> b >> k;
	//乘法增长更快
	if (k<=1)
	{
		//a和b转化为K进位，a*K就是在最后一位+1
		//当a变成b的数字的k进位制的前缀时，再用乘法，否则用加法
		cout << b - a << endl;
		return 0;
	}
	while (1)
	{
		if (a *k<= b)
		{
			ans += b % k + 1;
			b /= k;
		}
		else
		{
			ans += b - a;
			break;
		}
	}
	cout << ans << endl;
}