/*
【题目】sort使用技巧
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

/*#include <iostream>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
typedef struct Data {
	int x, y;
}data;
int check(int* arr, int size);
int* getRandDate(int n);
void Swap(int& n, int& m);
void out_put(int* arr, int size);
void output(vector<int>& arr, int size);
void _output(vector<Data>& arr, int size);
bool compare(const Data& a, const Data& b)
{
	if (a.x != b.x)
		return a.x > b.x;
	else 
		return a.y > b.y;
}
int main() 
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

	srand(time(0));
	//sort
	int* arr = getRandDate(10);
	sort(arr, arr + 10);//ҿ
	out_put(arr, 10);
	sort(arr, arr + 10, greater<int>());
	out_put(arr, 10);
	free(arr);
	//sortvector
	vector<int>arr1;
	for (int i = 0;i < 10;i++)
	{
		arr1.push_back(rand() % 10000);
	}
	output(arr1, arr1.size());
	sort(arr1.begin(), arr1.end(),greater<int>());
	output(arr1, arr1.size());
	//ԺṹĽ
	vector<Data> arr2;
	for (int i = 0;i < 10;i++)
	{
		Data a;
		a.x = rand() % 100;
		a.y = rand() % 100;
		arr2.push_back(a);
	}
	_output(arr2, 10);
	sort(arr2.begin(), arr2.end(),compare);
	_output(arr2, 10);
	//ԭϣݲ䣺±,СͬմС֣Сͬ±걾
	int* ind = getRandDate(10);
	for (int i = 0;i < 10;i++)ind[i] = i;
	 sort(a.begin(),a.end(),[&](int i,int j)->bool
      {
        if(nums[i]!=nums[j]) return nums[i]<nums[j];
        return i<j;
      });


	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return 0;
}
int check(int* arr, int size)//עsizeĴС
{
	for (int i = 0;i < size;i++)
	{
		if (arr[i] > arr[i + 1])

		{
			printf("wrong\n");
			return 0;
		}
	}
	printf("True\n");
	return 1;
}
int* getRandDate(int n)
{
	int* arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0;i < n;i++)
	{
		arr[i] = rand() % 10000;
	}
	return arr;
}
void Swap(int& n, int& m)
{
	int temp = n;
	n = m;
	m = temp;
}
void out_put(int* arr, int size)
{
	for (int i = 0;i < size;i++)
	{
		printf("%d  ", arr[i]);
	}
	printf("\n");
}
void output(vector<int>& arr, int size)
{
	for (int i = 0;i < size;i++)
	{
		printf("%d  ", arr.at(i));
	}
	printf("\n");
}
void _output(vector<Data>& arr, int size)
{
	for (int i = 0;i < size;i++)
	{
		printf("%d:  %d  %d  ", i, arr.at(i).x, arr.at(i).y);
	}
	printf("\n");
}*/