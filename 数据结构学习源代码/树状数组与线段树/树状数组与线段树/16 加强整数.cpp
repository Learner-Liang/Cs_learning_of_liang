/*
【题目】16 加强整数
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/


/*给出了一个长度为N的序列，元素下标从 1 到 N，你需要处理如下两种询问。

​ "C a b c"表示给[a, b]区间中的值全部增加c(-10000 ≤ c ≤ 10000)。

​ "Q a b" 询问[a, b]区间中所有值的和。*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define lowbit(x) (x)&(-x)
using namespace std;
void _add(int* c, int x, int k, int n)
{
// 步骤1（代码实现）：读取输入并完成必要初始化。
// 目的：把原始输入转化为程序可处理的数据状态。
// 实现：通过输入语句与初始赋值准备基础变量。
// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
// 目的：为核心转移/搜索/计算过程提供载体。
// 实现：用数组、容器或自定义结构存储中间状态与关系。
// 步骤3（代码实现）：执行核心算法流程。
// 目的：按照题意完成状态转移、搜索或计算求解。
// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	while (x <= n)
	{
		c[x] += k;
		x += lowbit(x);
	}
	

// 步骤4（代码实现）：输出结果并返回。
// 目的：给出最终答案并结束程序执行。
// 实现：调用输出语句打印结果，并通过 return 结束流程。
return;
}
int _query(int* c, int x)
{
	int sum = 0;
	while (x)
	{
		sum += c[x];
		x -= lowbit(x);
	}
	return sum;
}
int main16()
{

	//(k-i+1)xi   的总和x表示差分数组中的元素——》（k+1）xi and -i*xi
	// 一个传统的差分数组，一个由i*xi的数组
	//解决区域性问题用线段数组非常方便，但是这里用树状数组
	int n,m;
	int a[100] = { 0 };
	int x[2][100] = { 0 };
	cin >> n >> m;
	for (int i = 1;i <= n;i++)cin >> a[i];
	for (int i = 1;i <= n;i++)
	{
		_add(x[0], i, a[i] - a[i - 1], n);
		_add(x[1], i, i * (a[i] - a[i - 1]), n);
	}

	for (int i = 1,a,b,c;i <= m;i++)
	{
		char ch;
		cin >> ch;
		if (ch == 'C')
		{
			cin >> a >> b >> c;
			_add(x[0], a, c, n);
			_add(x[0], b+1, -c, n);
			_add(x[1], a, c * a, n);
			_add(x[1], b + 1, -c * (b+1), n);
		}
		else
		{
			cin >> a >> b;
			int sum = 0;
			sum += (b + 1)*_query(x[0], b);
			sum -= (a)*_query(x[0], a - 1);
			sum -= _query(x[1], b);
			sum += _query(x[1], a - 1);
			cout << sum << endl;
		}
	}
	return 0;
}