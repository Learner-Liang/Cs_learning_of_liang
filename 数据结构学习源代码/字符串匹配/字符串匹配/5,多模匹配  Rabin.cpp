#include <iostream>
#include <cmath>
using namespace std;
//通过哈希值判断
//单模匹配
#define MOD 9999
#define BASE 131
int hash_func(const char* t)
{
	int tlen = strlen(t);
	int kbase = 1, h = 0;
	for (int i = tlen-1;i>=0;i--)
	{
		h = (h + t[i]*kbase) % MOD;
		kbase *= BASE;
	}
	h = 0;
	for (int i = 0;t[i];i++)
		h = (h * BASE + t[i]) % MOD;
	return h;
}
int RabinKarp(const char* s, const char* t)
{
	int tlen, thash = hash_func(t);
	cout << thash << endl;
	int nbase = 1;
	for (tlen = 0;t[tlen];tlen++) nbase = (nbase*BASE)%MOD;
	int hash_s = 0;
	for (int i = 0;s[i];i++)
	{
		hash_s = (hash_s * BASE + s[i])%MOD;
		if (i + 1 < tlen)continue;
		if (i >= tlen)hash_s = (hash_s - s[i - tlen] * nbase % MOD + MOD) % MOD;
		cout << hash_s << "  ";
		if (hash_s != thash)continue;
		int flag = 1;
		for (int j = 0;j < tlen;j++)
		{
			if (s[i + j-tlen+1] == t[j])continue;
			flag = 0;
			break;
		}
		if (flag==1)return i-tlen+1;
	}
		return -1;
}
//多模匹配
int main5()
{

	char s[100], t[100];
	cin >> s >> t;
	cout << RabinKarp(s, t);
	return 0;
}