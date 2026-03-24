/*
lowbit函数
lowbit(i)代表i这个数字，二进制表示的最后一位i位权：从右往左，最后一位1代表的二进位制对应的值
1100表示4
lowbit(x)=x&(-x)
可以通过此函数遍历x的二进位制中每一位1
倒数第二位
lowbit=lowbit(x-lowbit(x))
*/


/*
改进前缀和：c[i]代表前lowbit(i)项的和：lowbit(12)=4    c[12]=c[12]+c[11]+c[10]+c[9]
查询：维护前缀和
前缀和s[i]=s[i-lowbit(i)]+c[i];
更新操作
a[j]元素改变：改变c[j]之后改变c[j+lowbit(j)]
*/
#include <iostream>
using namespace std;
#define lowbit(x) (x)&(-x)
//前缀和查询操作
int query100(int i,int* c)
{
	int sum = 0;
	while (i)
	{
		sum += c[i];
		i -= lowbit(i);
	}
	return sum;
}
//在原数组上加一个值操作
void add100(int i, int x, int n,int* c)
{
	while (i <= n)
	{
		c[i] += x;
		i += lowbit(i);
	}
	return;
}
int main8()
{
	int a[1000] = { 0 };
	int c[1000] = { 0 };
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> a[i];
		add100(i, a[i], n, c);
	}
	for (int i = 1;i <= n;i++)
	{
		cout << a[i] << "   ";
	}
	cout << endl;
	for (int i = 1;i <= n;i++)
		cout << c[i]<<"   ";
	cout << endl;
	for (int i = 1;i <= n;i++)
	{
		cout << query100(i,c)<<"   ";
	}
	return 0;
}