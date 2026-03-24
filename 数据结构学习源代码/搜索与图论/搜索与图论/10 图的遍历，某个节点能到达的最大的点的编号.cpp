#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define MAXL 100010

int N, M, A[MAXL];
vector<int> G[MAXL]; //vector存图 

void dfs(int x, int d) {
	if (A[x]) return; //访问过 
	A[x] = d;
	for (int i = 0; i < G[x].size(); i++)
		dfs(G[x][i], d);
}

int main() {
	int u, v;
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++) {
		scanf("%d%d", &u, &v);
		G[v].push_back(u); //反向建边 
	}
	for (int i = N; i; i--) dfs(i, i);
	for (int i = 1; i <= N; i++) printf("%d ", A[i]);
	printf("\n");
	return 0;
}
