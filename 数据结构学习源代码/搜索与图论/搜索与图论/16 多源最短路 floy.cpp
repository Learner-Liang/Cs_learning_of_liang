#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const long long NIF = 0x3f3f3f3f3f3f3f3f;
long long d[205][205], n, m;
void floy() {
    for (int k = 1;k <= n;k++) {
        for (int i = 1;i <= n;i++) {
            for (int j = 1;j <= n;j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            if (i == j)d[i][j] = 0;
            else d[i][j] =NIF;
        }
    }
    for (int i = 0, a, b, c;i < m;i++) {
        cin >> a >> b >> c;
        d[a][b] = c;
    }
    floy();
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= n;j++) {
            if (d[i][j] == NIF)cout << -1 << " ";
            else cout << d[i][j] << " ";
        }
        cout << endl;
    }
}