#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
vector<int>get_divisors(int n)//枚举约数
{
	vector<int>res;
	for (int i = 2;i <= n/i ;i++)
	{
		if (n % i == 0)
		{
			res.push_back(i);
			if (i != n / i)
			{
				res.push_back(n / i);
			}
		}
	}
	sort(res.begin(), res.end());//从小到大排序
	return res;
}
int num_divisors(int n)//求约数的个数
{
	int ans = 1;
	unordered_map<int,int>m;
	for (int i = 2;i <= n/i;i++)
	{
		while (n % i == 0)
		{
			m[i] += 1;
			n /= i;
		}
	}
	for (auto m1:m)ans = ans * (m1.second + 1);
	return ans;
}
int sum_divisors(int n)//求所有约数的和
{

	int ans = 1;
	unordered_map<int, int>m;
	for (int i = 2;i <= n / i;i++)
	{
		while (n % i == 0)
		{
			m[i] += 1;
			n /= i;
		}
	}
	for (auto m1 : m)
	{
		ans *= (pow(m1.first, m1.second + 1) - 1) / (m1.first-1);
	}
	return ans;
}
int gcd(int a, int b)//求最大公约数
{
	return b? gcd(b, a % b) :a;
}
//扩展欧几里得算法
int ex_gcd(int a, int b, int &x, int  &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int d= ex_gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
int main()
{
	int n;
	cin >> n;
	vector<int>res = get_divisors(n);
	for (int i = 0;i < res.size();i++)cout << res[i] << " ";
	cout << endl;
	cout << num_divisors(n) << endl;
	cout << sum_divisors(n) << endl;
	return 0;
}