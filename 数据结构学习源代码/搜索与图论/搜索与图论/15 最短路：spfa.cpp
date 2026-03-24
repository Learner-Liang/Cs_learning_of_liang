#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
int n, m, root;
typedef pair<int, int> P;
vector<P>h[1000];
int d[1000];
bool st[1000] = { 0 };
void spfa() {
	memset(d, 0x3f, sizeof(d));
	d[root] = 0;
	queue<int>q;
	q.push(root);
	st[root] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		st[cur] = 0;
		for (int i = 0, I = h[cur].size();i < I;i++) {
			if (d[cur] + h[cur][i].second < d[h[cur][i].first]) {
				d[h[cur][i].first] = d[cur] + h[cur][i].second;
				if (st[h[cur][i].first] == 0)q.push(h[cur][i].first);
				st[h[cur][i].first] = 1;
			}
		}
	}
	return;
}

int main() {
	cin >> n >> m >> root;
	for (int i = 0, a, b, c;i < m;i++) {
		cin >> a >> b >> c;
		h[a].push_back(P{b,c});
	}
	return 0;
}