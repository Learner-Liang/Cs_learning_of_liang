#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int n, m;
vector<int>edge[100005];
bool b[100005] = { 0 };
void dfs(int root) {
	cout << root << " ";
	for (int i = 0, I = edge[root].size();i < I;i++) {
		if (b[edge[root][i]])continue;
		b[edge[root][i]] = 1;
		dfs(edge[root][i]);
	}
	return;
}
void bfs(int root) {
	queue<int>q;
	q.push(root);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		cout << cur << " ";
		for (int i = 0, I = edge[cur].size();i < I;i++) {
			if (b[edge[cur][i]])continue;
			b[edge[cur][i]] = 1;
			q.push(edge[cur][i]);
		}
	}
	return;
}
int main() {
	cin >> n >> m;
	for (int i = 0, a, b;i < m;i++) {
		cin >> a >> b;
		edge[a].push_back(b);
	}
	for (int i = 1;i <= n;i++)sort(edge[i].begin(), edge[i].end());
	b[1] = 1;
	dfs(1);
	for (int i = 1;i <= n;i++)b[i] = 0;
	cout << endl;
	b[1] = 1;
	bfs(1);
	return 0;
}