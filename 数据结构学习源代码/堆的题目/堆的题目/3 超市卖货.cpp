/*
【题目】3 超市卖货
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

/*​ 超市里有N
个商品. 第i
个商品必须在保质期(第di
di
天)之前卖掉, 若卖掉可让超市获得pi
pi
的利润.每天只能卖一个商品.现在你要让超市获得最大的利润.*/
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <set>
//#include <pair>
using namespace std;
typedef struct Good
{
	int d;
	int val;
}Good;
Good good[10005] = { 0 };
typedef pair<int, int>p;
int n;
int main()
{
	int count = 0;
	cin >> n;
	for (int i = 0;i < n;i++)cin >> good[i].val >> good[i].d;
	sort(good, good + n, [&](const Good& a, const Good& b)->bool
		{
			if (a.d != b.d)return a.d < b.d;
			else return a.val > b.val;
		});
	set<p>s;
	s.insert(p{ good[0].val, count++ });
	for (int i = 1;i < n;i++)
	{
		if (good[i].d == s.size())
		{
			if (good[i].val > s.begin()->first)
			{
				s.erase(s.begin());
				s.insert(p{ good[i].val,count++ });
			}
		}
		else if (good[i].d > s.size())s.insert(p{ good[i].val,count++ });
	}
	int ans = 0;
	for (auto& x : s)
	{
		ans += x.first;
	}
	cout << ans;
	return 0;
}