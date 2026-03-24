// p1219 八皇后问题
#include <iostream>
#include <unordered_map>
using namespace std;
#define Max(n) ((1<<(n+1))-2)
unordered_map<int, int> ind;
int total = 3;
int arr[100] = { 0 };
void printf_( int n)
{
	if (total)
	{
		total--;
		for (int i = 1;i <= n;i++)
			printf("%d  ", arr[i]);
		printf("\n");
	}
}
int dfs(int k, int t1, int t2, int t3,int n)
{
	if (k > n)
	{
		printf_(n);
		return 1;
	}
	int ans = 0;
	for (int i = t1;i;i -= (i & (-i)))
	{
		int j = ind[i & (-i)];
		int a1 = (1 << (k + j - 1)), a2 = (1 << (k - j + n));
		if ((t2 & a1) && (t3 & a2))
		{
			arr[k] = j;
			ans += dfs(k + 1, t1 ^ (1 << j), t2 ^ a1, t3 ^a2, n);
		}

	}
	return ans;
}
int main1()
{
	//记录哪些数字被使用：用数组,此处每个皇后都是一样
	//优化：状态表示：状态压缩：将原来的数组改编为二进制数字
	//快速枚举：-t&t可以表示而二进制中最后一个数字（用补码储存）
	//倒数第二位：t-=(-t&t),再用上面公式
	//斜边只能放一个    正斜边：i+j-1得到的就是正斜边序号     反斜边i-j+n
	//再用二进制表示斜边是否可以使用
	int n;
	cin >> n;
	//用哈希表完成位权到二进位数字转换
	int m = 2 * n;
	for (int i = 0;i < m;i++) ind[1 << i] = i;
	int ans = 0;
	ans = dfs(1, Max(n), Max(m - 1), Max(m - 1),n);
	printf("%d\n", ans);
	return 0;
}