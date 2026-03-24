#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, k;
typedef struct Edge
{
	int a, b, w;
}Edge;
Edge edge[100];
int dis[100], backup[100];
int Bellmm_Ford()
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	for (int i = 0;i < k;i++)
	{
		memcpy(backup, dis, sizeof(dis));
		for (int j = 0;j < m;j++)
		{
			int a = edge[j].a, b = edge[j].b, w = edge[j].w;
			dis[b] = min(dis[b], backup[a] + w);
		}
	}
	if (dis[n] > 0x3f3f3f3f / 2)return -1;
	return dis[n];
}
int main()
{
	cin >> n >> m >> k;
	for (int i = 0, x, y, z;i < m;i++)
	{
		cin >> x >> y >> z;
		edge[i] = { x,y,z };
	}
	return 0;
}