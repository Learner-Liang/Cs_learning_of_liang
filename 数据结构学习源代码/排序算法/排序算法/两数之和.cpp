//排序，用首尾相加，小于目标值head左移动，大于tail右移
//由于要输出下表，因而不能改变原来数组的位置，只能改变下表
//#include <iostream>
//#include <vector>
//using namespace std;
//int main1()
//{
//	return 0;
//}
//vector<int> twoSum(vector<int>& nums, int target)
//{
//	int n = nums.size();
//	vector<int> ind(nums.size());
//	for (int i = 0;i < n;i++)
//	{
//		ind[i] = i;
//	}
//	//sort(ind.begin(), ind.end(), [&](int i, int j)->bool
//		{
//			return nums[i] < nums[j];
//		});
//	vector<int> a;
//	int head = 0, tail= n - 1;
//	while (1)
//	{
//		if (nums[ind[head]] + nums[ind[tail]] < target)
//		{
//			head++;
//		}
//		else if (nums[ind[head]] + nums[ind[tail]] > target)
//		{
//			tail--;
//		}
//		else
//		{
//			a.push_back(ind[head]);
//			a.push_back(ind[tail]);
//			break;
//		}
//	}
//	return  a;
//}