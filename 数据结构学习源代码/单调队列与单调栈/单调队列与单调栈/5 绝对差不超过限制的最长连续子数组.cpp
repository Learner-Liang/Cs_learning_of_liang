//绝对差不超过限制的子数组连续子集的最小值
//即同时维护一个区间内的最大值与最小值：使用两个单调队列同时维护一个区间
//设置为一个定长窗口，满足条件则将窗口向右扩大，不满足从左边缩小
#include <iostream>
#include <stack>
#include <deque>
#include <vector>
using namespace std;
class Solution {
public:
	int longestSubarray(vector<int>& nums, int limit) {
		deque<int>min_q, max_q;
		int n = nums.size();
		int head = 0;
		int length = 0;
		for (int tail = 0;tail < n;tail++)
		{
			while (!min_q.empty() && nums[tail] < nums[min_q.back()])
				min_q.pop_back();
			while (!max_q.empty() && nums[tail] > nums[max_q.back()])
				max_q.pop_back();
			min_q.push_back(tail);
			max_q.push_back(tail);
			while (nums[max_q.front()] - nums[min_q.front()] > limit)
			{
				if (max_q.front() == tail)
				{
					if (head == min_q.front())
						min_q.pop_front();
				}
				else
				{
					if (head == max_q.front())
						max_q.pop_front();
				}
				head++;
			}
			length = max(tail + 1 - head, length);
		}
		return length;
	}
};