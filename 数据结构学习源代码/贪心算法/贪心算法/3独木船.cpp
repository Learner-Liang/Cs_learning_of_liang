#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int main3()
{
	int w, n, a[30005] = { 0 };
	cin >> w >> n;
	for (int i = 0;i < n;i++)
		cin >> a[i];
	int head = 0, tail = n - 1, ans = 0;
	sort(a, a + n);
	while (head <= tail)
	{
		if (a[tail] + a[head] <= w)
		{
			tail--;
			head++;

		}
		else
			tail--;
		ans++;
	}
	cout << ans;
	return 0;
}