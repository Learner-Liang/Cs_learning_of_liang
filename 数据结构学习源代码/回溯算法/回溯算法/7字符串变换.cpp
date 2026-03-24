#include <iostream>
#include <string>
#include <cstring>
#include <map>
using namespace std;
string a[6], b[6];
int count1 = 0;//变换规则数
//迭代加深:控制加深的深度
int ans2 = 20, ans_k;
map<string, int> dp;//检测字符串出现的最短步骤
void dfs6(string A, string B, int step)
{
	if (step >= ans_k)return;
	//if (dp.find(A) != dp.end() && dp[A] <= step )return;
	dp[A] = step;
	if (A == B)
	{
		ans2 = step;
		return;
	}
	for (int i = 0;i < count1;i++)
	{
		int pos = -1;
		pos = A.find(a[i]);
		while (pos != -1)
		{
			string new_ = A;
			new_.erase(pos, a[i].size());
			new_.insert(pos, b[i]);
			if (dp.find(new_) == dp.end() || dp[new_] > step+1)
			dfs6(new_, B, step + 1);
			pos = A.find(a[i], pos + 1);
		}
	}
}
int main7()
{
	string A,B;
	cin >> A >> B;
	while (cin >> a[count1] >> b[count1])
	count1++;
	for (int i = 1;i <= 10;i++)
	{
		ans_k = i;
		dp.clear();
		dfs6(A, B, 0);//控制深度
		if (ans2 != 20)break;
	}
	cout << ans2 << endl;
	return 0;
}