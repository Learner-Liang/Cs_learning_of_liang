#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;
int double_vector(vector<int>A, vector<int>B)
{
	int n = A.size();
	deque<int>q1, q2;
	for (int i = 0;i < n;i++)
	{
		while (!q1.empty() && A[i] < A[q1.back()])q1.pop_back();
		while (!q2.empty() && B[i] < B[q2.back()])q2.pop_back();
		if (q1.size()!=q2.size())return i;
		q1.push_back(i);
		q2.push_back(i);
	}
	return n;
}
int main()
{
	int n;
	cin >> n;
	vector<int>A(n), B(n);
	for (int i = 0;i < n;i++)cin >> A[i] >> B[i];
	int ans = double_vector(A, B);
	cout << ans;
	return 0;
}