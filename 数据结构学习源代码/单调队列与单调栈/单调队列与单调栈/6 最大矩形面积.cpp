#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;
//逆向思维，最大举行的两边，必然是存在一个比最短木板短的木板
//两个单调栈分别维护最近左右两边的小于关系,一个也行
int main4()
{
	int n;
	cin >> n;
	vector<long long>arr(n + 2),l(n+2),r(n+2);//假设两边存在长度为0的木板
	for (int i = 1;i <= n;i++)
	{
		scanf("%lld", &arr[i]);
	}
	stack<int>q;
	q.push(0);
	for (int i = 1;i <= n;i++)
	{
		while (!q.empty() && arr[i] < arr[q.top()])
		{
			r[q.top()] = i;
			q.pop();
		}
		//l[i] = q.top();
		q.push(i);
	}
	//while (!q.empty())q.pop();
	//q.push(0);
	//for (int i = n;i>=0;i--)
	//{
	//	while (!q.empty() && arr[i] < arr[q.top()])
	//	{
	//		l[q.top()] = i;
	//		q.pop();
	//	}
	//	//r[i] = q.top();
	//	q.push(i);
	//}
	//两种都行
	while (!q.empty())
	{
		r[q.top()] = n+1;
		q.pop();
	}
	long long s = 0;
	for (int i = 1;i <= n;i++)
	{
		s = max(s, arr[i] * (r[i]-1 - l[i]));
	}
	cout << s;
	return 0;
}