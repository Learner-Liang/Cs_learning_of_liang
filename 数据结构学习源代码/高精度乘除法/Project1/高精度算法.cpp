#include <iostream>
#include <vector>
#include <string>
using namespace std;
// 高精度大数*小数
vector<int>multi(vector<int>arr, int a)
{
	vector<int>c;
	if (a == 0)
	{
		c.push_back(a);
		return c;
	}
	int t = 0;
	int n = arr.size();
	for (int i = 0;i < n;i++)
	{
		t = (arr[i]) * a+t;
		c.push_back(t%10);
		t /= 10;
	}
	while (t)
	{
		c.push_back(t % 10);
		t /= 10;
	}
	return c;
}
// 高精度小数除以常数
vector<int>div(vector<int>arr, int b)
{
	vector<int>c;
	int t = 0;
	int n = arr.size();
	for (int i = n - 1;i >= 0;i--)
	{
		c.push_back((arr[i] + t * 10) / b);
		t = (arr[i] + t * 10) % b;
	}
	reverse(c.begin(), c.end());
	while (*c.end() == 0)c.pop_back();
	return c;
}

// 高精度大数相乘
vector<int>multi_multi(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size(), n2 = b.size();
	for (int i = 0;i < n1;i++)
	{
		for (int j = 0;j < n2;j++)
		{
			if (i + j >= c.size())c.push_back(a[i] * b[j]);
			else c[i+j] += a[i] * b[j];
		}
	}
	int t = 0;
	int m = c.size();
	for (int i = 0;i < m || t;i++)
	{
		if(i<m)t = c[i] + t;
		if (i >= c.size())c.push_back(t % 10);
		else c[i] = t % 10;
		t /= 10;
	}
	return c;
}

int cmp(vector<int>a, vector<int>b)//比较两个高精度数的大小
{
	int n1 = a.size();
	int n2 = b.size();
	if (n1 != n2)return n1 < n2;
	for (int i = n1 - 1;i >= 0;i--)
	{
		if (a[i] != b[i])return a[i] < b[i];
	}
	return 0;//a大于b的时候返回0
}

//高精度大数相处
vector<int>div_div(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size();
	int n2 = b.size();
	if (cmp(a,b))
	{
		c.push_back(0);
		return  c;
	}
	int n = n1-1;
	int m = n2 - 1;
	//此时默认a>=b
	int k = 0;
	while (n >= m)
	{
		if (a[n] < b[m])
		{
			if(n!=0)//注意边界问题
			a[n-1] += a[n] * 10;
			n--;
			c.push_back(k);
			k = 0;
			continue;
		}
		int t = 0;
		int q = n - m;
		for (int i = 0;i <= m;i++)
		{
			a[q+i] -= b[i]+t;
			if (a[q + i] < 0)
			{
				a[q+ i] += 10;
				t = 1;
			}
			else
				t = 0;
		}
		k++;
	}
	reverse(c.begin(), c.end());
	while (c[c.size() - 1] == 0)c.pop_back();
	return c;
}
//直接用数组更方便
int main()
{
	/*高精度乘法
	string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = multi(arr, b);
	for (auto x : arr)cout << x;*/
	//高精度除法
	/*string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = div(arr, b);
	for (auto x : arr)cout << x;*/
	/*高精度*高精度
	string a, b;
	cin >> a >> b;
	vector<int>arr1, arr2;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	vector<int>c = multi_multi(arr1, arr2);
	int o = c.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << c[i];
	}*/
	//高精度除以高精度
	vector<int>arr1,arr2;
	string a, b;
	cin >> a >> b;
	vector<int>ans;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	ans = div_div(arr1, arr2);
	int o = ans.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << ans[i];
	}
	return 0;
}