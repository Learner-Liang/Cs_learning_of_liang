//将模式串变成字典树
#include <iostream>
using namespace std;
typedef struct Node
{
	int val ;
	Node* next[26];

}Node;
Node* getNewNode_()
{
	Node* p = (Node*)malloc(sizeof(Node));
	for (int i = 0;i < 26;i++)
		p->next[i] = NULL;
	p->val = 0;
	return p;
}
void insert__(const char* s, Node* root)
{
	Node* p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if(p->next[ind]==NULL)p->next[ind]=getNewNode_();
		p =p->next[ind];
	}
	p->val += 1;
	return;
}
int find_num(Node* root, const char* s)
{
	Node* p = root;
	int ans = 0;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (p->next[ind] == NULL)break;
		p = p->next[ind];
		ans += p->val;
	}
	return ans;
}
int main16()
{
	char t[100005] = { 0 }, s[100005] = { 0 };
	int n, m;
	cin >> n >> m;
	Node* root=getNewNode_();
	for (int i = 0;i < n;i++)
	{
		cin >> t;
		insert__(t, root);
	}
	for (int i = 0;i < m;i++)
	{
		cin >> s;
		int num = find_num(root, s);
		cout << num << endl;
	}
	return 0;
}