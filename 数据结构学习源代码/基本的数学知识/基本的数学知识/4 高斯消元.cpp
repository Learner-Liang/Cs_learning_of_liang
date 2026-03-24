#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
int n;

int gause(double**& martrix)
{
	int index, r = 0;
	for (int i = 0;i < n;i++)//枚举列
	{
		index = i;
		for (int j = i;j < n;j++)
		{
			if (abs(martrix[j][i] > martrix[index][i]))index = j;
		}

		if (abs(martrix[index][i]) < 1e-6)continue;



		double* temp = martrix[i];
		martrix[i] = martrix[index];
		martrix[index] = temp;


		for (int j = i + 1;j <= n;j++)martrix[r][j] /= martrix[r][i];
		martrix[r][i] = 1;

		for (int j = r + 1;j < n;j++)
		{
			if (martrix[j][i] > 1e-6)//如果小于，认为此行首位为0
				for (int g = n;g >= i;g--)
				{
					martrix[j][g] -= martrix[j][i] * martrix[r][g];
				}
		}
		r++;
	}
	//倒着消除一遍方程
	//此时只需要更新第n列的答案即可
	return  0;
	//缺少判断无解与无穷解的情况
}
int main()
{
	cin >> n;
	double** martrix = (double**)malloc(sizeof(double*) * n);
	for (int i = 0;i < n;i++) martrix[i] = (double*)malloc(sizeof(double) * (n + 1));
	for (int i = 0;i < n;i++)
	{
		for (int j = 0;j <= n;j++)
		{
			cin >> martrix[i][j];
		}
	}

	return 0;
}