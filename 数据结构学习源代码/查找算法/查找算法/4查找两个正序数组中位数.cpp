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