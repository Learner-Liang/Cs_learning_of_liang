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
using namespace std;
int n1,n2, m;
int h[100], e[100], ne[100], match[100] = { 0 };
bool st[100] = { 0 };
int cnt = 0;
void add_edge(int a, int b)
{
	e[cnt] = b;
	ne[cnt] = h[a];
	h[a] = cnt;
	cnt++;
	return;
}
bool find(int x) {
	for (int i = h[x];i != -1;i = ne[i]) {
		int j = e[i];
		if (!st[j]) {
			st[j] = 1;
			if (match[j] == 0 || find(match[j])) {
				match[j] = x;
				return 1;
			}
		}
	}
	return false;
}
int hangrian() {
	int res = 0;
	for (int i = 1;i <= n1;i++) {
		memset(st, 0, sizeof(st));
		if (find(i))res++;
	}
	return res;
}
int main() {
	cin >> n1 >> n2 >> m;
	for (int i = 1;i <= n1;i++)h[i] = -1;
	for (int i = 0, a, b;i < m;i++) {
		cin >> a >> b;
		add_edge(a, b);
	}

}