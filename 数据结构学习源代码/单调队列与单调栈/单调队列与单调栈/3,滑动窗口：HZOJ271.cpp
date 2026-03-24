#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <vector>
using namespace std;
//滑动窗口
int main()
{
	int num[300005] = { 0 };
	int max[300005] = { 0 };
	int min[300005] = { 0};
	int n, k;
	cin >> n >> k;
	for (int i = 0;i < n;i++)  scanf("%d", num + i);
	deque<int>s1, s2;
	for (int i = 0;i < n;i++)
	{
		while (!s1.empty() && num[s1.back()] > num[i])  s1.pop_back();
		while (!s2.empty() && num[s2.back()] < num[i])  s2.pop_back();
		if (i - s1.front() >= k)s1.pop_front();
		if (i - s2.front() >= k)s2.pop_front();
		s1.push_back(i);
		s2.push_back(i);
		if (i + 1 >= k)
		{
			min[i - k + 1] = num[s1.front()];
			max[i + 1 - k] = num[s2.front()];
		}
	}
	return 0;
}

//绝对差不超过限制的子数组连续子集的最小值
//即同时维护一个区间内的最大值与最小值：使用两个单调队列同时维护一个区间
//设置为一个定长窗口，满足条件则将窗口向右扩大，不满足从左边缩小
//class Solution {
//public:
//	int longestSubarray(vector<int>& nums, int limit) {
//		deque<int>min_q, max_q;
//		int n = nums.size();
//		int head = 0;
//		int length = 0;
//		for (int tail = 0;tail < n;tail++)
//		{
//			while (!min_q.empty() && nums[tail] < nums[min_q.back()])
//				min_q.pop_back();
//			while (!max_q.empty() && nums[tail] > nums[max_q.back()])
//				max_q.pop_back();
//			min_q.push_back(tail);
//			max_q.push_back(tail);
//			while (nums[max_q.front()] - nums[min_q.front()] > limit)
//			{
//				if (max_q.front() == tail)
//				{
//					if (head == min_q.front())
//						min_q.pop_front();
//				}
//				else
//				{
//					if (head == max_q.front())
//						max_q.pop_front();
//				}
//				head++;
//			}
//			length = max(tail + 1 - head, length);
//		}
//		return length;
//	}
//};