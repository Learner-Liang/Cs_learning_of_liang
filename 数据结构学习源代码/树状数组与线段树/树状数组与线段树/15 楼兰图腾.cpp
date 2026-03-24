/*在完成了分配任务之后，西部314来到了楼兰古城的西部。相传很久以前这片土地上(比楼兰古城还早)生活着两个部落，一个部落崇拜尖刀(‘V’)，
一个部落崇拜铁锹(‘∧’)，他们分别用V和∧的形状来代表各自部落的图腾。 西部314在楼兰古城的下面发现了一幅巨大的壁画，壁画上被标记出了N个点，
经测量发现这N个点的水平位置和竖直位置是两两不同的。
西部314认为这幅壁画所包含的信息与这N个点的相对位置有关，因此不妨设坐标分别为(1, y1), (2, y2), …, (n, yn), 其中y1...yn是1到n的一个排列。

​ 西部314打算研究这幅壁画中包含着多少个图腾，其中V图腾的定义如下（注意：图腾的形式只和这三个纵坐标的相对大小排列顺序有关）1≤i < j<k≤n且yi>yj, yj < yk;

​ 而崇拜∧的部落的图腾被定义为1≤i < j < k≤n且yi<yj, yj>yk;

​ 西部314想知道，这n个点中两个部落图腾的数目。因此，你需要编写一个程序来求出V的个数和∧的个数。*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define lowbit(x) (x)&(-x)
using namespace std;
//以中间的一个点，前面和后面小于和大于他的值
//树状数组可以用来统计前面有几个数字小于当前这位的数字
int query__(int* c, int ind)
{
	int sum = 0;
	while (ind)
	{
		sum += c[ind];
		ind -= lowbit(ind);
	}
	return sum;
}
void add__(int* c, int ind, int n)
{
	while (ind <= n)
	{
		c[ind]++;
		ind += lowbit(ind);
	}
	return;
}
void init(int* c, int n)
{
	for (int i = 1;i <= n;i++)
		c[i] = 0;
	return;
}
int main15()
{
	//开辟一个数组，去统计出现的数字，改成树状数组的形式，通过这个数组可以求的在当前位之前的数字出现了多少个
	//使用前缀和去维护
	int l[100] = { 0 };//i位置之前有多少个值小于
	int r[100] = { 0 };//i位置之后小于的数量给
	int a[100] = { 0 };
	int c[100] = { 0 };
	int n;
	cin >> n;
	for (int i = 1;i <= n;i++)cin >> a[i];
	for (int i = 1;i <= n;i++)
	{
		l[i] = query__(c, a[i]);
		add__(c, a[i], n);
	}
	init(c, n);
	for (int i = n;i ;i--)
	{
		r[i] = query__(c, a[i]);
		add__(c, a[i], n);
	}
	int ans1=0, ans2 = 0;
	for (int i = 1;i<=n;i++)
	{
		//cout << l[i] << " " << r[i] << endl;
		ans1 += l[i] * r[i];
		ans2 += (i - 1 - l[i]) * (n - i - r[i]);
	}
	cout << ans2 << " " << ans1;
	return 0;
}