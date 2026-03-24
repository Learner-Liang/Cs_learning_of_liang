/*
有 N 头牛站成一行。两头牛能够相互看见，当且仅当它们中间的牛身高都比它们矮。
现在，我们只知道其中最高的牛是第 P 头，它的身高是 H ，不知道剩余 N?1 头牛的身高。
但是，我们还知道 M 对关系，每对关系都指明了某两头牛 Ai,Bi 可以相互看见。求每头牛的身高最大可能是多少。
*/
#include <iostream>
#include <set>

using namespace std;
int main6()
{
	int x[1005] = { 0 };
	int n, p, h, m;
	set<pair<int, int>>s;
	cin >> n >> p >> h >> m;
	//注意事项：数据对可能并不是按照小到大给出
	//还要防止给出一摸一样的关系，要采用set去除重复
	x[1] = h;
	for (int i = 1, a, b;i < m;i++)
	{
		cin >> a >> b;
		if (a > b)swap(a, b);
		x[a + 1]--;
		x[b]--;
	}
	for (int i = 1;i <= m;i++)
	{
		x[i] += x[i - 1];
	}
	return 0;
}