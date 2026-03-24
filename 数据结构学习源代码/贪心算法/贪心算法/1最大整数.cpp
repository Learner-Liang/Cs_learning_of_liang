#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//string可以逐个直接比较
//A+B>B+A将A放在B前面，形成一个更长的字符串
int main1()
{
	vector<string>arr;
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		string s;
		cin >> s;
		arr.push_back(s);
	}
	sort(arr.begin(), arr.end(), [&](string a, string b)->bool {
		return a + b > b + a;
		});
	for (int i = 0;i < n;i++)
		cout << arr[i];
	return 0;
}