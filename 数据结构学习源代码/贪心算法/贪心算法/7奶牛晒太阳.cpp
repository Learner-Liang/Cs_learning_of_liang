#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;
typedef struct Scream {
	int power, num;
}scream;
typedef struct cows
{
	int l, r;
}cows;
bool cmp1(scream& a, scream& b)
{
	return a.power < b.power;
}

bool cmp2(cows& a, cows& b)
{
	if (a.r == b.r) return a.l < b.l;
	return a.r < b.r;
}
int main7()
{
	//将点从小到大，线段右端从小到大，左端也是
	cows arr1[2504] = { 0 };
	scream arr2[2504] = { 0 };
	int c, l;
	cin >> c >> l;
	for (int i = 0;i < c;i++)
	{
		scanf("%d%d", &arr1[i].l, & arr1[i].r);
	}
	for (int i = 0;i < l;i++)
	{
		scanf("%d%d", &arr2[i].power, &arr2[i].num);
	}
	sort(arr1, arr1 + c, cmp2);
	sort(arr2, arr2 + l, cmp1);
	int ans = 0;
	for (int i = 0;i < c;i++)
	{
		//不可行
		/*while (arr2[count].num == 0)count++;
		if (arr1[i].r < arr2[count].power)continue;
		if (arr1[i].l <= arr2[count].power)
		{
			ans++;
			arr2[count].num--;
		}
		else count++;*/
		for (int j = 0;j < l;j++)
		{
			if (arr2[j].num == 0)continue;;
			if (arr1[i].l <= arr2[j].power && arr1[i].r >= arr2[j].power)
			{
				arr2[j].num--;
				ans += 1;
				break;
			}
		}
	}
	cout << ans;
	return 0;
}