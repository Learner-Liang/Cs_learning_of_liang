#include <iostream>
#include <time.h>
using namespace std;
int n;
int* getRand(int n);
void downmain(int* a, int f);
int check(int* a, int f);
int main()
{
	srand(time(0));
	cin >> n;
	int* a = getRand(n);
	for (int i = n - 1;i >= 0;i--)
	{
		downmain(a, i);
	}
	if (check(a, 0))printf("OK\n");
	else printf("FALSE\n");
	return 0;
}
int* getRand(int n)
{
	int* a = (int*)malloc(sizeof(int) * n);
	for (int i = 0;i < n;i++)a[i] = rand() % 10000;
	return a;
}
void downmain(int* a, int f)
{
	if ((f*2+1)>=n)return;
	int ind = 0;
	if ((f*2+2==n)||a[f * 2 + 1] > a[f * 2 + 2])ind = f * 2 + 1;
	else ind = 2 * f + 2;
	if (a[f] < a[ind])
	{
		int temp = a[f];
		a[f] = a[ind];
		a[ind] = temp;
		downmain(a, ind);
	}
	return;
}
int check(int* a, int f)
{
	if ((2 * f + 1) >= n)return 1;
	int l = 2 * f + 1, r = 2 * f + 2;
	if (a[f] < a[l])return 0;
	if (r < n && a[f] < a[r])return 0;
	return check(a, l) && check(a, r);
}