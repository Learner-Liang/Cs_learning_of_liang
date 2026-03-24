#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//HZOJ 504
//找到第一个前一个比后一个大的值
//就是删除第一个距离最高位最近的逆序位
int main2()
{
	string s;
	cin >> s;
	int n;
	cin >> n;
	for (int i = 0;i < n;i++)
	{
		int k = s.size()-1;
		int j;
		for (j = 0;j < k;j++)
		{
			if (s[j] > s[j+1])break;
		}
		s.erase(s.begin() + j);
	}
	//开头为0
	while (*s.begin() == '0')
		s.erase(s.begin());
	cout << s;
	return 0;
}