
//有时候二叉树会退化为链表，因而用AVL树
//对于树的高度做出了限制，左右子树的高度差小于1
//注意平衡条件
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int val;
	Node* left, * right;
	int height;
}Node;
Node NIL = { -1,&NIL,&NIL,0 };
void out_put(Node* root);
Node* getNewNode(int val);
void clear(Node* root);
Node* insert(Node* root, int val);
void update_height(Node* root);
int max(int a, int b);
Node* maintain(Node* root);
Node* left_rotated(Node* root);
Node* right_rotated(Node* root);
Node* erase(Node* root, int val);
Node* pre_Node(Node* root);
Node* find(Node* root, int val);
int main()
{
	srand(time(NULL));
	Node* root = &NIL;
	for (int i = 0;i < 10;i++)
	{
		root = insert(root, rand() % 30);
	}
	out_put(root);
	int val = 1;
	while (val)
	{
		scanf("%d", &val);
		if (val == 1)root = insert(root, rand() % 30);
		else if (val == 2)root = erase(root, rand() % 30);
		out_put(root);
	}
	return 0;
}
void out_put(Node* root)
{
	if (root == &NIL)return;
	out_put(root->left);
	printf(" %d ", root->val);
	out_put(root->right);
	return;
}
Node* getNewNode(int val)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->val = val;
	temp->left = &NIL;
	temp->right = &NIL;
	temp->height = 1;
	return temp;
}
void clear(Node* root)
{
	if (root == &NIL)return;
	clear(root->left);
	clear(root->right);
	free(root);
	return;
}
Node* insert(Node* root, int val)
{
	if (root == &NIL)return getNewNode(val);
	if (root->val == val)return root;
	else if (root->val < val)root->right = insert(root->right, val);
	else root->left = insert(root->left, val);
	update_height(root);
	return maintain(root);
}
void update_height(Node* root)
{
	root->height = max(root->left->height, root->right->height) + 1;
	return;
}
int max(int a, int b)
{
	return a > b ? a : b;
}
Node* maintain(Node* root)
{
	if (abs(root->left->height - root->right->height) <= 1)return root;
	if (root->left->height > root->right->height)
	{
		if (root->left->left->height > root->left->right->height)
		{
			return right_rotated(root);
		}
		else
		{
			root->left = left_rotated(root->left);
			return right_rotated(root);
		}
	}
	else
	{
		if (root->right->right->height > root->right->left->height)
		{
			return left_rotated(root);
		}
		else
		{
			root->right = right_rotated(root->right);
			return left_rotated(root);
		}
	}
}
Node* left_rotated(Node* root)
{
	Node* r = root->right;
	root->right = r->left;
	r->left = root;
	update_height(r->left);
	//update_height(r->right);
	update_height(r);
	return r;
}
Node* right_rotated(Node* root)
{
	Node* l = root->left;
	root->left = l->right;
	l->right = root;
	update_height(root);
	update_height(l);
	return l;
}
Node* erase(Node* root, int val)
{
	if (root == &NIL)return root;
	if (root->val < val)
	{
		root->right = erase(root->right, val);
	}
	else if (root->val > val)
	{
		root->left = erase(root->left, val);
	}
	else
	{
		if ((root->left == &NIL) && (root->right == &NIL))
		{
			free(root);
			return &NIL;
		}
		else if (root->left == &NIL || root->right == &NIL)
		{
			Node* t = root->left == &NIL ? root->right : root->left;
			free(root);
			return t;
		}
		else
		{
			Node* p = pre_Node(root);
			root->val = p->val;
			root->left = erase(root->left, p->val);
		}
	}
	update_height(root);
	return maintain(root);
}
Node* pre_Node(Node* root)
{
	Node* temp = root->left;
	while (temp->right != &NIL)
	{
		temp = temp->right;
	}
	return temp;
}
Node* find(Node* root, int val)
{
	if (root == &NIL)return &NIL;
	if (root->val < val)return find(root->right, val);
	else if (root->val > val)return find(root->left, val);
	else return root;
}