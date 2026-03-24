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
#include <unordered_map>
#include <string>
using namespace std;
string s;
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int bfs()
{
	string end = "12345678X";
	queue<string>q;
	unordered_map<string, int>dis;
	dis[s] = 0;
	q.push(s);
	while (q.size())
	{
		string temp = q.front();
		if (temp == end)return dis[temp];
		q.pop();
		int t = 0;
		while (temp[t] == 'X')t++;
		int line = t / 3, column = t % 3;
		for (int i = 0;i < 4;i++)
		{
			int l = line + dx[i], c = column + dy[i];
			string te = temp;
			if (l <= 2 && l >= 0 && c <= 2 && c >= 0)
			{
				char c = temp[t];
				int position = l * 3 + c;
				te[t] = te[position];
				te[position] = c;
				if (dis.find(te) != dis.end())
				{
					dis[te] = dis[temp] + 1;
					q.push(te);
				}
			}
		}
	}
	return -1;
}
int main()
{
	char c;
	for (int i = 0;i < 9;i++)
	{
		cin >> c;
		s += c;
	}
	return 0;
}