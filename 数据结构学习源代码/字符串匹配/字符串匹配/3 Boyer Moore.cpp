#include <iostream>
using namespace std;
//没有成功匹配，模式串尽可能向后移动较大长度
// //移动长度取决与两条规则中较大值
// 匹配方向从后到前，找到不同时候要，将最后一次出现的模板串该字符与不同的对其，存在bug
//坏后缀原则

//好后缀原则
//以一个字符串为整体，j字符后的字符串的在j前面出现的最后一位字符的位置
//情况1：完全匹配
//部分汽匹配：从字符串开头
//j+=max(i-delta1[v],delta2[i]);滑动的距离
int BM(const char* s, const char* t);
int* getDelta1(const char* t);
int* getDelta2(const char* t);
int* searchEnd(const char* t);
int main3()
{
	char s[100], t[100];
	cin >> s >> t;
	cout << BM(s, t);
	return 0;
}
int BM(const char* s, const char* t)
{
	int* delta1 = getDelta1(t);
	int* delta2 = getDelta2(t);
	int slen = strlen(s), tlen = strlen(t);

	for (int j = 0;j + tlen <= slen;j++)
	{
		int tIndex = tlen - 1;
		while (tIndex >= 0 && s[j + tIndex] == t[tIndex])
			tIndex--;
		if (tIndex == -1)return j;
		j += max(tIndex-delta1[s[tIndex+j]], delta2[tIndex]);
	}
	return -1;
}
int* getDelta1(const char* t)
{
	int* delta = (int*)malloc(sizeof(int) * 256);
	int n = strlen(t);
	for (int i = 0;i<256;i++)delta[i] = -1;
	for (int i = 0;t[i];i++)
	{
		delta[t[i]] = i;
	}
	return delta;
}
int* searchEnd(const char* t)
{
	int n = strlen(t), m = n - 1;
	int* end = (int*)malloc(sizeof(int) * n);
	for (int i = 0;t[i];i++)
	{
		int j = 0;
		while (j <= i && t[i - j] == t[m - j])j++;
		end[i] = j;
	}
	return end;
}
int* getDelta2(const char* t)
{
	int tlen = strlen(t), lastInd = tlen - 1;
	int* end = searchEnd(t);
	int* delta = (int*)malloc(sizeof(int) * tlen);
	for (int i = 0;t[i];i++) delta[i] = tlen;//完全不存在好后缀及其子缀的时候，移动整个
	for (int i = 0;t[i];i++)
	{
		if (end[i] != i + 1)continue;
		int k = lastInd - end[i];
		//部分相同
		for (int j = 0;j <= k;j++)
		{
			delta[j] = lastInd - i;
		}
		//全部相同
		for (int i = 0;i<lastInd;i++)
		{
			delta[lastInd - end[i]] = lastInd - i;
		}
	}
	delta[lastInd] = 0;
	return delta;
}