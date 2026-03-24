#include <iostream>
using namespace std;
int main5()
{
	int l, m;
	cin >> l >> m;
	int num[1000] = { 0 };
	num[0] = 1;
	for (int i = 0, x, y;i < m;i++)//l+1个位置，每个位置都是1，差分数组除了第一个是1其余都是0
	{
		cin >> x >> y;
		num[x] -=1;
		num[y + 1] +=1;
	}
	int ans = 0, sum = 0;
	/*for (int i = 0;i <= l;i++)
	{
		sum += num[i];
		if (sum == 1)ans++;//sum等于前缀和，前缀和为1表示此处有树
	}*/
	cout << ans;
	return 0;
}