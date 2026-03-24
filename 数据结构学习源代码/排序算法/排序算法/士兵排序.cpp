#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <algorithm>
#define max 0x3f3f3f3f
using namespace std;
int main()
{
	int n;
	int x[10005];
	int y[10005];
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		scanf("%d  %d", x + i, y + i);
	}
	sort(x, x + n);
	sort(y, y + n);
	int maxx = x[n-1], maxy = y[n-1], minx = x[0], miny = y[0];
	int mindistance1 = 0x3f3f3f3f,mindistance2=0x3f3f3f3f;
	for (int j = miny;j <= maxy;j++)
	{
		int temp1 = 0;
		for (int i = 0;i < n;i++)
		{
			temp1 += abs(y[i]-j);
		}
		if (temp1 < mindistance1)
	       mindistance1 = temp1;
	}
	//优化：与货舱选址类似，一律取中间值
	for (int i = minx-n;i <= maxx+n;i++)
	{
		int temp2 = 0;
		for (int j = 0;j < n;j++)
			temp2 += abs(x[j] - i - j);
		if (temp2 < mindistance2)
			mindistance2 = temp2;
	}
	//x-i-x[i],将x排序后i减去下表，再进行货舱选址
	int distance = mindistance1 + mindistance2;
	cout << distance;
	return 0;
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
	using namespace std;
	int x[10005] = { 0 }, y[10005] = { 0 };
	int n;
	int main()
	{
		cin >> n;
		for (int i = 0;i < n;i++)scanf("%d %d", x + i, y + i);
		sort(x, x + n);
		sort(y, y + n);
		int ans = 0;
		for (int head = 0, tail = n - 1;head < tail;head++, tail--)ans += y[tail] - y[head];
		for (int i = 0;i < n;i++)x[i] -= i;
		sort(x, x + n);
		for (int head = 0, tail = n - 1;head < tail;head++, tail--)ans += x[tail] - x[head];
		cout << ans;
		return 0;
	}
}