//（i，j）单调队列维护以j位置结尾的单调递增序列，维护区间最值
//入队操作：队尾如队，会把之前破坏单调性的元素从队尾移出
//出对操作：如果对首超出区间范围，就将与那苏从队首移出
//队首元素，是当前区间最值
//维护区间最小值，创建单增队列，反而反之
//区间中每个元素，每个都会进队一次，也会出队一次
//均摊时间复杂度为2.
#include <iostream>
#include <queue>
#include <deque>
using namespace std;
int main1()
{
	int n, k;
	cin >> n >> k;
	deque<int>q;//q可以存储值或者数组的下标，但是最好存储数组的下标，因为不存在信息损失
	vector<int>arr;
	for (int i = 0,a;i < n;i++)
	{
		cin >> a;
		arr.push_back(a);
	}
	for (int i = 0;i < n; i++)
	{
		cout << arr[i] << "  ";
	}
	for (int i = 0;i < n;i++)
	{
		while (!q.empty() && arr[q.back()] > arr[i])
		q.pop_back();
		q.push_back(i);
		if (i - q.front() == k)//当前元素的下标与队首下标差大于区间范围
		q.pop_front();
		printf("[%d %d]", max(i-k+1,0), i);
	}
	return 0;
}