   #include <iostream>
using namespace std;

int sunday(const char* s, const char* t);
int main2()
{
	char s[100], t[100];
	cin >> s >> t;
	cout << sunday(s, t);
	return 0;
}
//每一次匹配失败，根据起点加模板穿的长度，将模板串与该位对齐，因为i到i+m位的匹配失败，要后移
//由于选取的为最后一个字符，如果滑动低于此距离，必然没有匹配
int sunday(const char* s, const char* t)
{
	int len[256] = { 0 }, n=strlen(s),m = strlen(t);//len记录某个字符咋模板中出现的最后一次位置，倒数的方式
	for (int i = 0;i < 256;i++)len[i] = m + 1;
	for (int i = 0;t[i];i++)len[t[i]] = m - i;
	for (int i = 0;i + m <= n;i += len[s[i + m]])
	{
		int flag = 1;
		for (int j = 0;t[j];j++)
		{
			if (s[i + j] == t[j])
				continue;
			flag = 0;
			break;
		}
		if (flag == 1)return i;
	}
	return -1;
}