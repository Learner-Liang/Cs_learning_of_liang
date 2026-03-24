#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
typedef pair<int, int> P;
int d[1000], g[1000][1000];
bool st[1000] = { 0 };
int n, m, root;
void dijstra() {
	memset(d, 0x3f, sizeof(d));
	d[root] = 0;
	for (int i = 0;i < n;i++) {
		int t = -1;
		for (int j = 1;j <= n;j++) {
			if (st[j] == 0 && (t == -1 || d[t] > d[j]))t=j;
		}
		st[t] = 1;
		for (int j = 1;j <= n;j++) {
			if (d[j] > d[t] + g[t][j])d[j] = d[t] + g[t][j];
		}
	}
	return;
}

//堆优化
void dijstra() {
	memset(d, 0x3f, sizeof(d));
	d[root] = 0;
	set<P>s;
	s.insert(P{ 0,root });
	while (!s.empty()) {
		auto cur = *s.begin();
		s.erase(s.begin());
		int ver = cur.second, distance = cur.first;
		if (st[ver])continue;
		st[ver] = 1;
		//下面省略，用灵界表更快
	}
}
int main() {
	cin >> n >> m >> root;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= i;j++) {
			g[i][j] = g[j][i] = 0x3f3f3f3f;
		}
	}
	for (int i = 0,a,b,c;i < m;i++) {
		cin >> a >> b >> c;
		g[a][b] = g[b][a] = c;
	}
	return 0;
}