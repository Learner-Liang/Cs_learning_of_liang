//微扰:让第i+1位为最大，与第i位调整：经过推算，可以得知，左右手乘积小的放在前面
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define SIZE 10000
typedef struct human
{
	int l, r;
};
vector<int>ans, temp;
//乘法
void multipy(int x);
vector<int>divide(int x);
vector<int>compare(vector<int>a, vector<int>b);
human m[10005] = { 0 };
int main()
{
	int n;
	cin >> n;
	for (int i = 0;i <= n;i++)scanf("%d %d", &m[i].l, &m[i].r);
	sort(m + 1, m + n + 1, [&](human a, human b)->bool
		{
			return a.l * a.r < b.l * b.r;
		});
	temp.push_back(m[0].l);
	for (int i = 1;i <= n;i++)
	{
		ans = compare(ans, divide(m[i].r));
		multipy(m[i].l);
	}
	printf("%d", ans[ans.size() - 1]);
	for (int i = ans.size() - 2;i >= 0;i--)printf("%4d", ans[i]);
	return 0;
}
void multipy(int x)
{
	int n = temp.size();
	int t = 0;
	for (int i = 0;i < n;i++)
	{
		temp[i] = temp[i] * x + t;
		temp[i] = temp[i] % SIZE;
		t = temp[i] / SIZE;
	}
	while (t)
	{
		temp.push_back(t % SIZE);
		t /= SIZE;
	}
	return;
}
vector<int>divide(int x)
{
	vector<int>t = temp;
	int g = 0;
	for (int i = t.size() - 1;i >= 0;i--)
	{
		t[i] += g * SIZE;
		g = t[i] % x;
		t[i] /= x;
	}
	while (!t.empty() && t.back() == 0)t.pop_back();
	if (t.empty()) {
		t.push_back(0);
	}
	return t;
}
vector<int>compare(vector<int>a, vector<int>b)
{
	int n1 = a.size(), n2 = b.size();
	if (n1 != n2)return n1 < n2 ? b : a;
	for (int i = n1 - 1;i >= 0;i--)
	{
		if (a[i] != b[i])return a[i] > b[i] ? a : b;
	}
	return a;
}