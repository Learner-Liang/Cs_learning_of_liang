/*
【题目】3 Boyer Moore
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

#include <iostream>
using namespace std;
//ûгɹƥ䣬ģʽƶϴ󳤶
// //ƶȡнϴֵ
// ƥ䷽ӺǰҵͬʱҪһγֵģ崮ַ벻ͬĶ䣬bug
//׺ԭ

//ú׺ԭ
//һַΪ壬jַַjǰֵһλַλ
//1ȫƥ
//ƥ䣺ַͷ
//j+=max(i-delta1[v],delta2[i]);ľ
int BM(const char* s, const char* t);
int* getDelta1(const char* t);
int* getDelta2(const char* t);
int* searchEnd(const char* t);
int main3()
{
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	char s[100], t[100];
	cin >> s >> t;
	cout << BM(s, t);

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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
	for (int i = 0;t[i];i++) delta[i] = tlen;//ȫںú׺׺ʱƶ
	for (int i = 0;t[i];i++)
	{
		if (end[i] != i + 1)continue;
		int k = lastInd - end[i];
		//ͬ
		for (int j = 0;j <= k;j++)
		{
			delta[j] = lastInd - i;
		}
		//ȫͬ
		for (int i = 0;i<lastInd;i++)
		{
			delta[lastInd - end[i]] = lastInd - i;
		}
	}
	delta[lastInd] = 0;
	return delta;
}