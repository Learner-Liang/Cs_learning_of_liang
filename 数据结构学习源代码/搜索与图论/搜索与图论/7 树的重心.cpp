#include <iostream>
#include <vector>
using namespace std;
bool st[1000] = { 0 };
vector<int>h[1000];
int n,m;
int ans = 0;

int dfs(int root) {
	st[root] = 1;
	int res = 0, sum = 1;
	for (int i = 0, I = h[root].size();i < I;i++) {
		if (st[h[root][i]])continue;
		int s = dfs(h[root][i]);
		res = max(res, s);
		sum += s;
	}
	res = max(res, n - res);
	ans = max(res, ans);
	return sum;
}
int main() {
	cin >> n >> m;
	for (int i = 0, a, b;i < m;i++) {
		cin >> a >> b;
		h[a].push_back(b);
		h[b].push_back(a);
	}
	dfs(1);
	cout << ans;
	return 0;
}