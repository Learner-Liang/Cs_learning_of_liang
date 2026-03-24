#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main4()
{
	int n,half, ans=0;
	cin >> n;
	half = n / 2;
	int arr[1005] = { 0 };
	for (int i = 1;i <= n;i++)arr[i] = 1;
	for (int i = 2;i <= n;i++)
	{
		for (int j = i / 2;j >= 1;j--)
		{
			arr[i] += arr[j];
		}
	}
	cout << arr[n];
	return 0;
}