#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
#define r(a,b) sqrt((a)*(a)+(b)*(b))
struct {
	int x, y;
}pos[1005];
int main5()
{
	int n, d, ans = 0;
	cin >> n >> d;
	for (int i = 0,a;i < n;i++)
	{
		scanf("%d%d",&pos[i].x,&a);
		pos[i].y = a;
		if (a > d || -a > d)
		{
			cout << "-1";
			return 0;
		}
	}
	sort(pos, pos + n, [&](const auto a, const auto b) -> bool {
		return (a.x + sqrt(d * d - a.y * a.y)) <
			(b.x + sqrt(d * d - b.y * b.y));
		});
	int i = 0;
	while(i<n)
	{
		int x = sqrt(d * d - pos[i].y * pos[i].y) + pos[i].x;
		ans++;
		i++;
		while (i<n && r(pos[i].x - x, pos[i].y) <= d)i++;
	}
	cout << ans << endl;
	//处理方法L:设置区间，对于一个雷达，再此区间内设置以一个雷达就可以
	//之后将区间结束位置排序，雷达放在末尾
	/*struct Range {
		double l, r;
	} arr[MAX_N + 5];

	bool cmp(const Range & a, const Range & b) {
		return a.r < b.r;
	}

	int main() {
		int n;
		double r, x, y, pos;
		cin >> n >> r;
		for (int i = 0; i < n; i++) {
			cin >> x >> y;
			if (y > r) {
				cout << -1 << endl;
				return 0;
			}
			double delta = sqrt(r * r - y * y);
			arr[i].l = x - delta;
			arr[i].r = x + delta;
		}
		sort(arr, arr + n, cmp);
		int ans = 1;
		pos = arr[0].r;
		for (int i = 1; i < n; i++) {
			if (arr[i].l > pos) {
				ans += 1;
				pos = arr[i].r;
			}
		}
		cout << ans << endl;
		return 0;
	}*/
	return 0;
}