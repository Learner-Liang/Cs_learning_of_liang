#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int count2 = 0;
//做跨越性dp的时候，先改成单纯dp之后用单纯dp表示跨越性dp
//p3174
struct EDGe
{
	int son_val, son;
};
int m_ans = 0;
int fa[100] = { 0 };
void _add_(int* head, EDGe* edge, int a, int b)
{
	edge[++(count2)] = { b,head[a] };
	head[a] = count2;
	fa[a] += 1;
	return;
}
int dp_[100] = { 0 };
void get_dp_(int* head, EDGe* edge, int fa, int son);
int main9()
{
	int n, m;
	cin >> n >> m;
	EDGe edge[100];
	int head[100] = { 0 };
	for (int i = 0, a, b;i < m;i++)
	{
		scanf("%d%d", &a, &b);
		_add_(head, edge, a, b);
		_add_(head, edge, b, a);
	}
	get_dp_(head, edge, 0, 1);
	cout << m_ans;
	return 0;
}
void get_dp_(int* head, EDGe* edge, int f, int son)
{
	dp_[son] = 1;
	int x1 = 0, x2=0;
	for (int p = head[son];p;p = edge[p].son)
	{
		int to = edge[p].son_val;
		if (to == f)continue;
		get_dp_(head, edge, son, to);
		if (dp_[to] > x1) x2 = x1,x1 = dp_[to];
		else if (dp_[to] > x2)x2 = dp_[to];
	}
	m_ans = max(m_ans, x1 + x2 + fa[son] - 1);
	dp_[son]=max(dp_[son],fa[son] + x1-1);
	return;
}