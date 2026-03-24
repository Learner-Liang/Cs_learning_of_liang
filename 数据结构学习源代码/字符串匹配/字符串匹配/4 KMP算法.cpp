#include <iostream>
using namespace std;
//最长前缀信息储存在next数组中，next[i],next[j]=k表示以j位置结尾的后缀等于k结尾的位置的前缀，长度为k
//1  2  3  4
//   1  2  3  4
int* initnext(const char* t);
int KMP(const char* s, const char* t);
int main4()
{
	char s[100], t[100];
	cin >> s >> t;
	cout << KMP(s, t);
	return 0;
}
int* initnext(const char* t)
{
	int n = strlen(t);
	int* next = (int*)malloc(sizeof(int) * n);
	next[0] = -1;
	int j = -1;
	for (int i = 1;i < n;i++)
	{
		while (j!=-1&&t[j + 1] != t[i])
		{
			j = next[j];
		}
		if (t[j + 1] == t[i]) j++;
		next[i] = j;
	}
	return next;
}
int KMP(const char* s, const char* t)
{
	int* next = initnext(t);
	int j = -1;//j指向匹配的模式串的位置
	int tlen = strlen(t);
	for (int i = 0;s[i];i++)
	{
		while (j != -1 && s[i] != t[j + 1])j = next[j];
		if (s[i] == t[j + 1])j += 1;
		if (t[j + 1] == 0)return i - tlen + 1;
	}
	return -1;
}