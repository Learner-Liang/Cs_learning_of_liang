#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main2()
{
	int n;
	cin >> n;
	int f[505] = { 0 };
	f[1] = 0;
	f[2] = 1;
	f[3] = 1;
	for (int i = 4;i <= n;i++)
	{
		if (f[i - 2])f[i] += f[i - 2];
		if (f[i - 3])f[i] += f[i - 3];
	}
	cout << f[n];
	return 0;
}