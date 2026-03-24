#include <iostream>
using namespace std;
int main2()
{
	int s[100] = { 0 };
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> s[i];
		s[i] += s[i - 1];//优化：将数组本身改造为前缀和纾尊
	}
	return 0;
}