//洛谷 ：p1083
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>

using namespace std;
int n1, m1;
struct order {
	int d, s, t;
};
int x[1000] = { 0 };
int a[1000] = { 0 };
order ods[1000];
bool check(int mid)
{
	for (int i = 1;i <= n1;i++)
	{
		x[i] = a[i] - a[i - 1];
	}
	for (int i = 1;i <= mid;i++)
	{
		x[ods[i].s] -= ods[i].d;
		x[ods[i].t+1] += ods[i].d;
	}
	long long sum = 0;
	for (int i = 1;i <= n1;i++)
	{
		sum += x[i];
		if (sum < 0)return 1;
	}
	return 0;
}
int binary_search(int l,int r)
{
	int mid;
	while (l < r)
	{
		mid = (l + r) / 2;
		if (check(mid))r = mid;
		else l = mid + 1;
	}
	return l;
}
//二分法的技巧：右边r=m+1;
//如果全部都是0，则指向m+1位，输出全部满足需要的结果 
int main7()
{
	//二分法：前i个订单都能满足为0出现不能满足订单都是1找到最后一个1
	//差分前缀和：进行差分后在进行求前缀和的操作，判断区间内每个数字是否大于等于0
	//直接遍历也可以，但是速度会满很多，慢在求前缀和
	cin >> n1 >> m1;
	for (int i = 1;i <=n1;i++)  scanf("%d", a + i);
	for (int i = 1;i <= m1;i++)  scanf("%d%d%d", &(ods[i].d), &ods[i].s, &ods[i].t);
	/*int flag = 1;
	long long sum = 0;
	for (int i = 1;i <= n;i++) x[i] = a[i] - a[i-1];*/
	/*int i;
	for (i = 1;i <= m;i++)
	{
		x[ods[i].s] -= ods[i].d;
		x[ods[i].t + 1] += ods[i].d;
		for (int j = 1;j <= ods[i].t;j++)
		{
			sum += x[j];
			if (sum < 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
		{
			break;
		}
		sum = 0;
	}
	if (flag == 0)cout << "-1" << endl << i;
	else cout << 0;*/
	int ind = binary_search(1, m1 + 1);
	if (ind!= m1+1)cout << "-1" << endl << ind;
	else cout << 0;
	return 0;
}