#include <iostream>
using namespace std;
//逐个匹配
int brute_force(const char* s, const char* t);//返回找到的位置
int main1()
{
	char s[100], t[100];
	cin >> s >> t;
	printf("%d", brute_force(s,t));
	return 0;
}
int brute_force(const char* s,const char* t)
{
	for (int i = 0;s[i];i++)
	{
		int flag = 0;
		for (int j = 0;t[j];j++)
		{
			if (s[i + j] == t[j])continue;
			flag == 1;
			break;
		}
		if (flag == 0)return i;
	}
	//找不到返回-1
	return -1;
}