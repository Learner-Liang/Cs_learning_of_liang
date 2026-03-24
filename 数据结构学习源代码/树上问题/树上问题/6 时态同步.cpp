#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
/*小 Q 在电子工艺实习课上学习焊接电路板。一块电路板由若干个元件组成，我们不妨称之为节点，并将其用数字 1,2,3⋯ 进行标号。
电路板的各个节点由若干不相交的导线相连接，且对于电路板的任何两个节点，都存在且仅存在一条通路（通路指连接两个元件的导线序列）。

在电路板上存在一个特殊的元件称为“激发器”。当激发器工作后，产生一个激励电流，通过导线传向每一个它所连接的节点。
而中间节点接收到激励电流后，得到信息，并将该激励电流传向与它连接并且尚未接收到激励电流的节点。
最终，激励电流将到达一些“终止节点”――接收激励电流之后不再转发的节点。

激励电流在导线上的传播是需要花费时间的，对于每条边 e，激励电流通过它需要的时间为 t 
​
 ，而节点接收到激励电流后的转发可以认为是在瞬间完成的。现在这块电路板要求每一个“终止节点”同时得到激励电路――即保持时态同步。
 由于当前的构造并不符合时态同步的要求，故需要通过改变连接线的构造。目前小 Q 有一个道具，使用一次该道具，
 可以使得激励电流通过某条连接导线的时间增加一个单位。请问小 Q 最少使用多少次道具才可使得所有的“终止节点”时态同步？*/
struct edge
{
	int first = 0, second = 0;
	int t = 0;
};
int _cnt = 0;
void __add(edge* edge, int* head, int a, int b, int price)
{
	edge[++_cnt] = { b,head[a],price };
	head[a] = _cnt;
	return;
}
int dp11[100] = { 0 }, t1[100] = { 0 };
void dps2(edge* edge, int* head, int f, int s)
{
	int p = head[s];
	while (p)
	{
		int to = edge[p].first;
		if (to != f)
		{
			dps2(edge, head, s, to);
			t1[s] = max(t1[s], t1[to] + edge[p].t);
		}
		p = edge[p].second;
	}
	p = head[s];
	while (p)
	{
		int to = edge[p].first;
		if (to != f)
		{
			dp11[s] += t1[s] - edge[p].t - t1[to] + dp11[to];
		}
		p = edge[p].second;
	}
	return;
}
int main6()
{
	//不是在终止节点使用，而是在每一层就调节好，因为到达每个终止节点应该是一样的，对于一颗子树而言，到达每个终止节点是一样的
	int n, s;
	cin >> n>> s;
	int head[100] = { 0 };
	edge edge[100];
	for (int i = 1,a,b,c;i < n;i++)
	{
		scanf("%d%d%d", &a, &b, &c);
		__add(edge, head, a, b, c);
		__add(edge, head, b, a, c);
	}
	dps2(edge, head,0,s );
	cout << dp11[s];
	return 0;
}