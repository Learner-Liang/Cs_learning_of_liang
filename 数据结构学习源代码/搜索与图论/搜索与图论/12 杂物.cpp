#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int main() {
	int n;
	cin >> n;
	int ans = 0;
	vector<int>t(n + 1,0);
	for (int i = 1, len;i <= n;i++) {
		cin >> i >> len;
		int j;
		while (cin >> j && j) {
			t[i] = max(t[i], t[j]);
		}
		t[i] += len;
		ans = max(ans, t[i]);
	}
	cout << ans;
	return 0;
}