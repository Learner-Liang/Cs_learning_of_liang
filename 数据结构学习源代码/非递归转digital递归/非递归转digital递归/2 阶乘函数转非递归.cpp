#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>
using namespace std;
struct data
{
	data(int g, int* p)
	{
		n = g;
		pre_ret = p;
		code = 0;
		return;
	}
	int n;
	int code, ret, * pre_ret;
};
int f(int n)
{
	if (n == 1)return 1;
	return n * f(n - 1);
}
int non_f(int n)
{
	stack<struct data>s;
	int ans;
	struct data c(n, &ans);
	s.push(c);
	while (!s.empty())
	{
		struct data& cur = s.top();
		switch (cur.code)
		{
		case 0:
		{
			if (cur.n == 1)
			{
				*(cur.pre_ret) = 1;
				s.pop();
			}
			else
			{
				cur.code = 1;
			}
			break;
		}
		case 1:
		{
			s.push(struct data(cur.n - 1, &cur.ret));
			cur.code = 2;
			break;
		}
		case 2:
		{
			*cur.pre_ret = cur.n * cur.ret;
			s.pop();
			break;
		}
		}
	}
	return ans;
}
int main()
{
	int n;
	while (1)
	{
		cin >> n;
		cout << non_f(n) << endl;
	}
	return 0;
}