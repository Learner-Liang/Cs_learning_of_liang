//并查集用来解决连通性问题
//连通性问题：对于集合中的点进行联通和查询和合并的过程
#include <iostream>
using namespace std;
//1，基于染色思想，一开始所有点颜色不同
//2，连接操作就是将两个点变为同意颜色
//3，相同颜色的点就是联通的
#define num 10005
int color[num];
void init(int n);
//联通判断，合并操作
int find(int a);
//quick_find
//若干节点都可以间接指向同一节点
 //是否联通判断快
int merge(int a, int b ,int n);
void output(int n);
int main()
{
	int a, b, n;
	cin >> n;
	init(n);
	while (scanf_s("%d %d", &a, &b))
	{
		
		if (merge(a, b, n))
			printf("merge %d with %d.\n", a, b);
		output(n);
	}
	return 0;
}
void init(int n)
{
	for (int i = 0;i < n;i++)color[i] = i;
	return;
}
int find(int a)
{
	return color[a];
}
int merge(int a, int b,int n)
{
	int aa = find(a), bb = find(b);
	if (aa == bb)return 0;
	for (int i = 0;i < n;i++)
	{
		if (color[i] == aa)color[i] = bb;
	}
	return 1;
}
void output(int n)
{
	for (int i = 0;i < n;i++)
	{
		printf("%3d: %d", i, color[i]);
	}
	printf("\n");
}

 