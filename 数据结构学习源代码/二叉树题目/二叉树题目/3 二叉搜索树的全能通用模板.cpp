#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <queue>
//#include <pair>
using namespace std;
typedef struct Node
{
	struct Node* left = NULL, * right = NULL;
	int val;
	int cnt = 1;
	int size = 1;
}Node;
Node* root1 = NULL;
Node* getNode1(Node* root, int val);
int preNode(Node* root, int x);
int lastNode(Node* root, int x);
int query(Node* root, int x);
int ratings(Node* root, int x, int ans);
int main()
{
	int q;
	cin >> q;
	for (int i = 0, x, y;i < q;i++)
	{
		scanf("%d %d", &x, &y);
		if (x == 5)root1 = getNode1(root1, y);
		else if (x == 4)
		{
			if (lastNode(root1, y) == 0)cout << "2147483647" << endl;
		}
		else if (x == 3)
		{
			if (root1->val >= y && root1->left == NULL)cout << "−2147483647" << endl;
			else preNode(root1, y);
		}
		else if (x == 2)query(root1, y);
		else if (x == 1)ratings(root1, y, 1);
	}
	return 0;
}
Node* getNode(Node* root, int val) {

	if (root == NULL) {

		Node* newNode = (Node*)malloc(sizeof(Node));

		newNode->val = val;

		newNode->cnt = 1;

		newNode->size = 1;

		newNode->left = newNode->right = NULL;

		return newNode;

	}

	if (val < root->val) {

		root->left = getNode(root->left, val);

	}
	else if (val > root->val) {

		root->right = getNode(root->right, val);

	}
	else {

		root->cnt++;

	}

	// 更新当前节点的size为左子树size + 右子树size + 当前cnt

	root->size = root->cnt;

	if (root->left) root->size += root->left->size;

	if (root->right) root->size += root->right->size;

	return root;

}
Node* getNode1(Node* root, int val)
{
	if (root == NULL)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));

		newNode->val = val;

		newNode->cnt = 1;

		newNode->size = 1;
		newNode->left = newNode->right = NULL;
		return newNode;
	}
	if (val < root->val)
	{
		root->left = getNode(root->left, val);
	}
	else if (val > root->val)
	{
		root->right = getNode(root->right, val);
	}
	else
	{
		root->cnt++;
	}
	root->size = root->cnt;
	if (root->left) root->size += root->left->size;
	if (root->right) root->size += root->right->size;
	return root;
}
int preNode(Node* root, int x)
{
	if (root == NULL)return 0;
	if (root->val >= x)
	{
		return preNode(root->left, x);
	}
	else
	{
		if (root->right != NULL)
		{
			if (preNode(root->right, x) == 0)
			{
				cout << root->val << endl;
				return 1;
			}
			return 1;
		}
		else cout << root->val << endl;
		return 1;
	}
}
int lastNode(Node* root, int x)
{
	if (root == NULL)return 0;
	if (root->val <= x)
	{
		return (lastNode(root->right, x));
	}
	else
	{
		if (lastNode(root->left, x) == 0)
		{
			cout << root->val << endl;
			return 1;
		}
		return 1;
	}
}
int query(Node* root, int x)
{
	if (root->left == NULL)
	{
		if (x <= root->cnt)cout << root->val << endl;
		else query(root->right, x - root->cnt);
		return 0;
	}
	if (x <= root->left->size)
	{
		query(root->left, x);
		return 0;
	}
	else if (x <= root->left->size + root->cnt)
	{
		cout << root->val << endl;
		return 0;
	}
	else query(root->right, x - (root->left->size + root->cnt));
	return 0;
}
int ratings(Node* root, int x, int ans)
{
	if (root->val > x)
	{
		if (root->left == NULL)cout << ans << endl;
		else ratings(root->left, x, ans);
		return 0;
	}
	else if (root->val == x)
	{
		if (root->left != NULL)
		{
			ans += root->left->size;
			cout << ans << endl;
		}
		else cout << ans << endl;
		return 0;
	}
	else
	{
		if (root->left)ans += root->left->size;
		ans += root->cnt;
		if (root->right != NULL)ratings(root->right, x, ans);
		else cout << ans;

	}
	return 0;
}