/*
ã€é¢˜ç›®ã€‘é«˜ç²¾åº¦ç®—æ³•
ã€æ•´ä½“ç®—æ³•æ€è·¯ã€‘
æ­¥éª¤1ï¼šè¯»å–è¾“å…¥å¹¶å®Œæˆåˆå§‹åŒ–ã€‚
ç›®çš„ï¼šå°†é¢˜ç›®æ•°æ®è½¬æ¢ä¸ºå¯è®¡ç®—çš„çŠ¶æ€ã€‚
æ­¥éª¤2ï¼šå»ºç«‹æœ¬é¢˜éœ€è¦çš„æ•°æ®ç»“æ„/çŠ¶æ€å®šä¹‰ã€‚
ç›®çš„ï¼šä¸ºåç»­æ ¸å¿ƒç®—æ³•æä¾›æ­£ç¡®çš„ä¿¡æ¯ç»„ç»‡æ–¹å¼ã€‚
æ­¥éª¤3ï¼šæ‰§è¡Œæ ¸å¿ƒç®—æ³•æµç¨‹ï¼ˆè§ä¸‹æ–¹å…³é”®å‡½æ•°æˆ–å¾ªç¯ï¼‰ã€‚
ç›®çš„ï¼šæŒ‰é¢˜æ„é€æ­¥æ±‚è§£å¹¶å¾—åˆ°æœ€ç»ˆç­”æ¡ˆã€‚
æ­¥éª¤4ï¼šè¾“å‡ºç»“æœå¹¶ç»“æŸç¨‹åºã€‚
ç›®çš„ï¼šè¿”å›é¢˜ç›®è¦æ±‚çš„ç»“æœï¼Œå®Œæˆä¸€æ¬¡å®Œæ•´æ±‚è§£ã€‚
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;
// ¸ß¾«¶È´óÊı*Ğ¡Êı
vector<int>multi(vector<int>arr, int a)
{
	vector<int>c;
	if (a == 0)
	{
		c.push_back(a);
		return c;
	}
	int t = 0;
	int n = arr.size();
	for (int i = 0;i < n;i++)
	{
		t = (arr[i]) * a+t;
		c.push_back(t%10);
		t /= 10;
	}
	while (t)
	{
		c.push_back(t % 10);
		t /= 10;
	}
	return c;
}
// ¸ß¾«¶ÈĞ¡Êı³ıÒÔ³£Êı
vector<int>div(vector<int>arr, int b)
{
	vector<int>c;
	int t = 0;
	int n = arr.size();
	for (int i = n - 1;i >= 0;i--)
	{
		c.push_back((arr[i] + t * 10) / b);
		t = (arr[i] + t * 10) % b;
	}
	reverse(c.begin(), c.end());
	while (*c.end() == 0)c.pop_back();
	return c;
}

// ¸ß¾«¶È´óÊıÏà³Ë
vector<int>multi_multi(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size(), n2 = b.size();
	for (int i = 0;i < n1;i++)
	{
		for (int j = 0;j < n2;j++)
		{
			if (i + j >= c.size())c.push_back(a[i] * b[j]);
			else c[i+j] += a[i] * b[j];
		}
	}
	int t = 0;
	int m = c.size();
	for (int i = 0;i < m || t;i++)
	{
		if(i<m)t = c[i] + t;
		if (i >= c.size())c.push_back(t % 10);
		else c[i] = t % 10;
		t /= 10;
	}
	return c;
}

int cmp(vector<int>a, vector<int>b)//±È½ÏÁ½¸ö¸ß¾«¶ÈÊıµÄ´óĞ¡
{
	int n1 = a.size();
	int n2 = b.size();
	if (n1 != n2)return n1 < n2;
	for (int i = n1 - 1;i >= 0;i--)
	{
		if (a[i] != b[i])return a[i] < b[i];
	}
	return 0;//a´óÓÚbµÄÊ±ºò·µ»Ø0
}

//¸ß¾«¶È´óÊıÏà´¦
vector<int>div_div(vector<int>a, vector<int>b)
{
	vector<int>c;
	int n1 = a.size();
	int n2 = b.size();
	if (cmp(a,b))
	{
		c.push_back(0);
		return  c;
	}
	int n = n1-1;
	int m = n2 - 1;
	//´ËÊ±Ä¬ÈÏa>=b
	int k = 0;
	while (n >= m)
	{
		if (a[n] < b[m])
		{
			if(n!=0)//×¢Òâ±ß½çÎÊÌâ
			a[n-1] += a[n] * 10;
			n--;
			c.push_back(k);
			k = 0;
			continue;
		}
		int t = 0;
		int q = n - m;
		for (int i = 0;i <= m;i++)
		{
			a[q+i] -= b[i]+t;
			if (a[q + i] < 0)
			{
				a[q+ i] += 10;
				t = 1;
			}
			else
				t = 0;
		}
		k++;
	}
	reverse(c.begin(), c.end());
	while (c[c.size() - 1] == 0)c.pop_back();
	return c;
}
//Ö±½ÓÓÃÊı×é¸ü·½±ã
int main()
{
	/*¸ß¾«¶È³Ë·¨
	string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = multi(arr, b);
	for (auto x : arr)cout << x;*/
	//¸ß¾«¶È³ı·¨
	/*string a;
	cin >> a;
	int n = a.size();
	vector<int>arr;
	for (int i = n - 1;i >= 0;i--)arr.push_back(a[i] - '0');
	int b;
	cin >> b;
	arr = div(arr, b);
	for (auto x : arr)cout << x;*/
	/*¸ß¾«¶È*¸ß¾«¶È
	string a, b;
	cin >> a >> b;
	vector<int>arr1, arr2;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	vector<int>c = multi_multi(arr1, arr2);
	int o = c.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << c[i];
	}*/
	//¸ß¾«¶È³ıÒÔ¸ß¾«¶È
	vector<int>arr1,arr2;
	string a, b;
	cin >> a >> b;
	vector<int>ans;
	int n1 = a.size();
	int n2 = b.size();
	for (int i = n1 - 1;i >= 0;i--)
		arr1.push_back(a[i] - '0');
	for (int i = n2 - 1;i >= 0;i--)
		arr2.push_back(b[i] - '0');
	ans = div_div(arr1, arr2);
	int o = ans.size();
	for (int i = o - 1;i >= 0;i--)
	{
		cout << ans[i];
	}
	return 0;
}