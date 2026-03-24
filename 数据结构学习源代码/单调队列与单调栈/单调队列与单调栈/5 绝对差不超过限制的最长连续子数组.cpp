/*
【题目】5 绝对差不超过限制的最长连续子数组
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

//ԲƵӼСֵ
//ͬʱάһڵֵСֵʹͬʱάһ
//Ϊһڣ򽫴󣬲С
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
				// 步骤1（代码实现）：读取输入并完成必要初始化。
				// 目的：把原始输入转化为程序可处理的数据状态。
				// 实现：通过输入语句与初始赋值准备基础变量。
				// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
				// 目的：为核心转移/搜索/计算过程提供载体。
				// 实现：用数组、容器或自定义结构存储中间状态与关系。
				// 步骤3（代码实现）：执行核心算法流程。
				// 目的：按照题意完成状态转移、搜索或计算求解。
				// 实现：通过循环、递归或转移方程推进计算直到得到答案。

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

				// 步骤4（代码实现）：输出结果并返回。
				// 目的：给出最终答案并结束程序执行。
				// 实现：调用输出语句打印结果，并通过 return 结束流程。
			}
			length = max(tail + 1 - head, length);
		}
		return length;
	}
};