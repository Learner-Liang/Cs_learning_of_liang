#include <iostream>
using namespace std;
int arr1[10] = { 0 };
void dfs8(int max, int n, int mis)
{
	if (mis == 0)
	{
		if (n < 2)return;
		for (int i = 0;i < n;i++)

		{
			printf("%d", arr1[i]);
			if (i != n - 1)printf("+");
		}
		cout << endl;
		return;
	}
	if (max > mis)return;
	for (int i = max;i <= mis;i++)
	{
		arr1[n] = i;
		dfs8(i, n + 1, mis - i);
	}
	return;
}
int main8()
{
	int n;
	cin >> n;
	dfs8(1, 0, n);
	return 0;
}