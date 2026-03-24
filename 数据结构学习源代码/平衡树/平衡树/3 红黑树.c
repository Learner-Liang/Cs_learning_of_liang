//每个节点非黑即红
//根节点是黑色
//叶节点（NIL)是黑色
//红节点的两个子节点是黑色
//从根节点到所有叶节点的路径上，黑色节点数量相同
// 
// 
//最短路径与最长路径比值为2，最短：全部黑色，最长：黑红相间
// 
//插入调整站在祖父节点，删除调整站在父节点看，插入删除五种情况
//由路径上黑色节点数量相等可知，插入的节点为黑色会失衡，红色可能会失衡，因为红色的子节点不为黑色会失衡
//调整前后每条路径的黑色节点的数量不能改变
//1，子节点与父节点为红，树父节点为红色：父节点和叔父节点变为黑色，祖父节点变红
//2，叔父节点为黑色：LL类型：右旋，变为黑红红（红色上浮）或者红黑黑（红色下沉）
//3,LR类型类似：先小左旋，再右旋，RR，RL类比即可
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int key, color;//0:红色 1：黑色 2：双重黑
	struct Node* left, * right;
}Node;
Node NIL;
void init_NIL()
{
	NIL.key = -1;
    NIL.color = 1;
	NIL.left = &NIL;
	NIL.right = &NIL;
	return;
}
Node* getNewNode();
void clear();
Node* insert();
Node* insert_maintain();
int has_red_node();
Node* left_rotated(Node* root);
Node* right_rotated(Node* root);
void output(Node* root);
Node* _insert(Node* root, int key);
Node* erase(int key,Node* root);
Node* _erase();
Node* preNode();
Node* erase_maintain();
int main()
{
	init_NIL();
	srand(time(NULL));
	Node* root = &NIL;
	for (int i = 0;i < 100;i++)
	{
		int key = rand() % 150;
		root=_insert(root, key);
		printf("insert %d\n", key);
		output(root);
	}
	printf("\n");
	int x;
	while (~scanf_s("%d", &x))
	{
		if (x == -1)break;
		root = erase(x, root);
		output(root);
		printf("\n");
	}
	return 0;
}
Node* getNewNode(int key)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->key = key;
	p->left = &NIL;
	p->right = &NIL;
	p->color = 0;
	return p;
}
void clear(Node* root)
{
	if (root == &NIL)return;
	clear(root->left);
	clear(root->right);
	free(root);
}
Node* insert(int key, Node* root)
{
	if (root == &NIL)return getNewNode(key);
	if (root->key == key)return root;
	if (key < root->key) root->left = insert(key,root->left);
	else if (key > root->key) root->right = insert( key,root->right);
	return insert_maintain(root);
}
Node* _insert(Node* root, int key)
{
	root = insert(key, root);
	root->color = 1;
	return root;
}
Node* insert_maintain(Node* root)//调节
{
	int flag = 0;
	if ((root->left->color == 0) && has_red_node(root->left))flag = 1;
	if ((root->right->color == 0) && has_red_node(root->right))flag = 2;
	if (flag == 0)return root;
	if (root->left->color == root->right->color)
	{
		root->color = 0;
		root->left->color = 1;
		root->right->color = 1;
		return root;
	}
	if (flag == 1)
	{
		if (root->left->right->color == 0)//LR
		{
			root->left = left_rotated(root->left);
		}
		root = right_rotated(root);//LL
	}
	else
	{
		if(root->right->left->color==0)//RL
		{
			root->right = right_rotated(root->right);
		}
		root = left_rotated(root);//RR
	}
	root->color = 0;
	root->left->color = 1;
	root->right->color = 1;
	return root;
}
int has_red_node(Node* root)
{
	return root->left->color == 0 || root->right->color == 0;
}
Node* left_rotated(Node* root)
{
	Node* p = root->right;
	root->right = p->left;
	p->left = root;
	return p;
}
Node* right_rotated(Node* root)
{
	Node* p = root->left;
	root->left = p->right;
	p->right = root;
	return p;
}
void output(Node* root)
{
	if (root == &NIL)return;
	output(root->left);
	printf("%d[%d]  ", root->key, root->color);
	output(root->right);
	return;
}
Node* erase(int key,Node* root)
{
	root = _erase(key, root);
	root->color = 1;//不加上此处，最高点可能为双重黑
	return root;
}
Node* _erase(int key, Node* root)
{
	if (root == &NIL)return root;
	if (key < root->key)root->left = _erase(key, root->left);
	else if(key > root->key)root->right = _erase(key, root->right);
	else
	{
		if (root->left == &NIL || root->right == &NIL)//有一个子节点或者0个子节点,至少一个NIL，父节点为红色时候wu节点
		{
			Node* temp = (root->left != &NIL) ? root->left : root->right;
			temp->color+= root->color;//将子节点节点的颜色改为父节点后销毁父节点
			//父为黑，子必为红或者NIL，->黑或者双重黑，父为红，子为NIL  
			free(root);
			return temp;
		}
		Node* temp = preNode(root);
		root->key = temp->key;
		root->left = _erase(root->left,temp->key);
	}
	return erase_maintain(root);
}
Node* erase_maintain(Node* root)
{
	if (root->left->color != 2 && root->right->color != 2)return root;
	//兄弟节点为红色
	if (has_red_node(root))
	{
		root->color = 0;//旧的节点改为红色
		if (root->left->color == 0)
		{
			root = right_rotated(root);//此节点不会是最后一位，因为右边是双重黑i，因而至少还有一个黑色
			root->right = erase_maintain(root->right);

		}
		else
		{
			root = left_rotated(root);//此节点不会是最后一位，因为右边是双重黑i，因而至少还有一个黑色
			root->left = erase_maintain(root->left);
		}
		root->color = 1;//新的节点改为黑色
		return root;
	}
	if ((root->left->color == 2 && !has_red_node(root->right))|| (root->right->color == 2 && !has_red_node(root->left)))//情况1
	{
		root->color += 1;
		root->left->color -= 1;
		root->right->color -= 1;
		return root;
	}
	if (root->right->color == 2)//RL
	{
		root->right->color= 1;
		if (root->left->right->color==0)//RR
		{
			root->left = left_rotated(root->left);
		}
		root->left->color -= root->color;
		root = right_rotated(root);
	}
	if (root->left->color == 2)
	{
		root->left->color = 1;
		if (root->right->left->color == 0)
		{
			root->right = right_rotated(root->right);
		}
		root->right->color -= root->color;
		root = left_rotated(root);
	}
	root->left->color = 1;
	root->right->color = 1;
	return root;
}
Node* preNode(Node *root)
{
	Node* p = root->left;
	while (p->right != &NIL) p = p->right;
	return p;
}