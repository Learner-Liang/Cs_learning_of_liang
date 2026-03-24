//删除了从头部出元素的操作
//因而。单调栈就是不从队首出元素的单调队列
#include <iostream>
#include <stack>
#include <vector>
//栈中存储下标，可以认为相邻两个序列元素中，下标之间的值，对应的数组元素，比前一个大，因而，
// 前一个没有被弹出栈，比后一个也大，但是后一个大于前一个
//单增栈
//单调栈维护最近小于关系，此元素能把哪个元素弹出，则此元素就是在数组序列中，
// 距离被弹出元素最近的比此元素小的元素
// //单减栈维护最近大于关系
//从左边入栈，就是维护左边最近关系
//从数组右向左，就是从右边入栈，维护右边最近关系

using namespace std;
int main2()
{
	stack<int>s;
	int n;
	cin >> n;
	vector<int> arr;
	arr.push_back(-1);
	for (int i = 0,a;i < n;i++)
	{
		cin >> a;
		arr.push_back(a);
	}
	arr.push_back(10);
	int m =n+ 2;
	vector<int>r(m), l(m);
	for (int i = 0;i < m;i++)
	{
		cout << arr[i] << "  ";
	}
	
	for (int i = 0;i < m;i++)
	{
		while (!s.empty() && arr[s.top()] > arr[i])
		{
			r[s.top()] = i;
			//右侧距离被弹出元素最近的
			//数组下标为被弹出元素的下标
			//数组储存的值是最近元素的下标
			s.pop();
		}
		s.push(i);
	}
	printf("\n");
	for (int i = 0;i < m;i++)
	{
		cout << l[i] << "  ";
	}
	for (int i = m-1;i>=0;i--)
	{
		while (!s.empty() && arr[s.top()] > arr[i])
		{
			l[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	printf("\n");
	for (int i = 0;i < m;i++)
	{
		cout << r[i] << "  ";
	}
	return 0;
}