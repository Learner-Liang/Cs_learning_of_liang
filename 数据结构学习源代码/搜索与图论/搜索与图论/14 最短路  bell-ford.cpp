#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef struct edge {
	int a, b, w;
}edge;
int n, m, cnt = 0, k;
edge e[1000];
int d[1000], back[1000];
int bellman_ford() {
	memset(d, 0x3f, sizeof(d));
	d[1] = 1;
	for (int i = 0;i < k;i++) {
		memcpy(back, d, sizeof(d));
		for (int j = 0;j < m;j++) {
			d[e[j].b] = min(d[e[j].b], back[e[j].a] + e[j].w);
		}
	}
}
int main() {
	cin >> n >> m >> k;
	for (int i = 0, a, b, c;i < m;i++) {
		cin >> a >> b >> c;
		e[cnt++] = { a,b,c };
	}
}