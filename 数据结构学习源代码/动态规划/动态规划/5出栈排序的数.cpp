#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main5()
{
	int n;
	cin >> n;
	int f[20] = { 0 };
	f[0] = f[1] = 1;
	f[2] = 2;
	for (int i = 3;i <= n;i++)
	{
		for (int j = 1;j <= i;j++)
		{
			f[i] +=f[j-1]*f[i-j];//对于3以后的，分别以之前的每一个为最后一个出栈的元素
		}
	}
	cout << f[n] << endl;
	return 0;
}