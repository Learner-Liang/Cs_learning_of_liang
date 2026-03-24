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
	srand(time(0));
	//sort对数组进行排序
	int* arr = getRandDate(10);
	sort(arr, arr + 10);//左闭右开
	out_put(arr, 10);
	sort(arr, arr + 10, greater<int>());
	out_put(arr, 10);
	free(arr);
	//sort对vector进行排序
	vector<int>arr1;
	for (int i = 0;i < 10;i++)
	{
		arr1.push_back(rand() % 10000);
	}
	output(arr1, arr1.size());
	sort(arr1.begin(), arr1.end(),greater<int>());
	output(arr1, arr1.size());
	//对含结构体的进行排序
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
	//对于原数组进行排序但是希望数组内容不变：对下标数组进行排序,大小不同按照大小划分，大小相同按照下标本身
	int* ind = getRandDate(10);
	for (int i = 0;i < 10;i++)ind[i] = i;
	 sort(a.begin(),a.end(),[&](int i,int j)->bool
      {
        if(nums[i]!=nums[j]) return nums[i]<nums[j];
        return i<j;
      });

	return 0;
}
int check(int* arr, int size)//注意size的大小
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