#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
using namespace std;
/*巴蜀国的社会等级森严，除了国王之外，每个人均有且只有一个直接上级，当然国王没有上级。
如果 A 是 B 的上级，B 是 C 的上级，那么 A 就是 C 的上级。绝对不会出现这样的关系：A 是 B 的上级，B 也是 A 的上级。

最开始的时刻是 0，你要做的就是用 1 单位的时间把一个消息告诉某一个人，
让他们自行散布消息。在任意一个时间单位中，任何一个已经接到消息的人，都可以把消息告诉他的一个直接上级或者直接下属。

现在，你想知道：
到底需要多长时间，消息才能传遍整个巴蜀国的所有人？
要使消息在传递过程中消耗的时间最短，可供选择的人有那些？*/
struct edge
{
	int f = 0, s = 0;
}e[100];
int cnt = 0;
int nm;
int dp[100] = { 0 }, head[100] = { 0 };
int num[100] = { 0 };
int tail = -1;
void add( int a, int b)
{
	e[++cnt] = { b,head[a] };
	head[a] = cnt;
	return;
}
void getDp(int f, int s);
void initdp();
int g = 1;
int main7()
{
	cin >> nm;
	for (int i = 2,a;i <= nm;i++)
	{
		scanf("%d", &a);
		add(a, i);
		add(i, a);
	}
	int mi = 0x3f3f3f3f;
	//枚举每一个人作为节点的根节点值
	for (int i = 1;i <= nm;i++)
	{
		initdp();
		getDp(0,i);
		if (mi < dp[i])continue;
		else if (mi == dp[i])
		{
			num[++tail] = i;
		}
		else
		{
			mi = dp[i];
			tail = -1;
			num[++tail] = i;
		}
	}
	cout << mi << endl;
	for (int i = 0;i <= tail;i++)
		cout << num[i] << " ";
	return 0;
}
void getDp(int f, int s)
{
	for (int p = head[s];p;p = e[p].s)
	{
		int to = e[p].f;
		if (to == f)continue;
		getDp(s, to);
		dp[s] = max(dp[s], dp[to]+1);//可能存在相等的值，改为vector数组存储
	}
	return;
}
void initdp()
{
	for (int i = 1;i <= cnt;i++)dp[i] = 0;
	return;
}