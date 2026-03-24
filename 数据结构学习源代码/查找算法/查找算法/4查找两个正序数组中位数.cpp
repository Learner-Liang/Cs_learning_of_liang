/*
【题目】4查找两个正序数组中位数
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

//#include <iostream>
//#include <vector>
//using namespace std;
//int main()
//{
//	return 0;
//}
//int findk(vector<int>& n1, int ind1, vector<int>& n2, int ind2, int k)
//{
//	if (k == 1)
//	{
//		int a = (n1.size() == ind1 ? 1000000 : n1[ind1]);
//		int b = (n2.size() == ind2 ? 1000000 : n2[ind2]);
//		return min(a, b);
//	}
//	if (ind1 == n1.size())  return n2[ind2 + k - 1];
//	if (ind2 == n2.size())  return n1[ind1 + k - 1];
//	int cnt1 = min(k / 2, n1.size() - ind1);
//	int cnt2 = min(k - cnt1, n2.size() - ind2);
//	cnt1 = k - cnt1;
//	if (n1[ind1 + cnt1 - 1] < n2[ind2 + cnt2 - 1])
//	{
//		ind1 = ind1 + cnt1;return (n1, ind1, n2, ind2, k-cnt1);
//		
//	}
//	else
//	{
//		ind2 = ind2 + cnt2;return (n1, ind1, n2, ind2, k-cnt2);
//	}
//
//}