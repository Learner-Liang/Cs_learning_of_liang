#include <iostream>
#include <deque>
#include <stack>
#include <vector>
using namespace std;
//最大子序列和：求数组元素之和：前缀和数组
int main()
{
	deque<int>p;
	int n, m;
	cin >> n >> m;
	vector<int>v(n + 1);
	v[0] = 0;
	for (int i = 0, a;i < n;i++)
	{
		scanf("%d", &a);
		v[i + 1] = v[i] + a;
	}
	int max_ = 0;
	for (int i = 0;i <= n;i++)
	{
		while (!p.empty() && v[i] < v[p.back()])p.pop_back();
		p.push_back(i);
		if (i - p.front() > m)p.pop_front();
		max_ = max(max_, v[i] - v[p.front()]);
	}
	cout << max_;
	return 0;
}