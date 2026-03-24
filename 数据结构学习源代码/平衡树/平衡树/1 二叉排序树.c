//性质：
//1，左子树<右子树
//2,右子树>根节点
//解决与排名相关的检索需求
//插入：比根大右，否则左
//删除：当前根节点为2：找到前驱或者后继度为1以下的与当前根节点交换
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int key;
	struct Node* left, * right;
}Node;
Node* getNewNode();
void clearTree();
void clearNode();
Node* insert();
Node* erase(int key, Node* root);
Node* preNode(Node* root);
void output(Node* root)
{
	if (root == NULL)return;
	output(root->left);
	printf("  %d  ", root->key);
	output(root->right);
}
int main()
{
	srand(time(NULL));
	Node* root = NULL;
	for (int i = 0;i < 10;i++)
	{
	    int key = rand() % 10;
		printf("insert %d\n", key);
		root = insert(root, key);
    }
	printf("\n");
	output(root);
	return 0;
}
Node* getNewNode(int key)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->left = NULL;
	p->right = NULL;
	p->key = key;
	return p;
}
void clearTree(Node* root)
{
	if (root == NULL)return;
	clearTree(root->left);
	clearTree(root->right);
	clearNode(root);
	return;
}
void clearNode(Node* root)
{
	if (root == NULL) return;
	free(root);
}
Node* insert(Node* root,int key)
{
	if (root == NULL)return getNewNode(key);
	if (root->key == key)return root;
	if (key < root->key)root->left = insert(root->left, key);
	else root->right = insert(root->right, key);
	return root;
}
Node* erase(int key, Node* root)
{
	if (root == NULL)return root;
	if (key < root->key) root->left= erase(key, root->left);
	else if (key > root->key)  root->right=erase(key, root->right);
	else
	{
		if (root->left == NULL && root->right == NULL)
		{
			free(root);
			return NULL;
		}
		else if (root->left == NULL || root->right == NULL)
		{
			Node* temp = (root->left ? root->left : root->right);
			free(temp);
			return temp;
		}
		else
		{
			Node* temp = preNode(root);
			root->key = temp->key;
			root->left = erase(root->left, temp->key);
		}
	}
	return root;
}
Node* preNode(Node* root)
{
	Node* temp = root->left;
	while (temp->right)
	{
		temp = temp->right;
	}
	return temp;
}