/*
【题目】3 红黑树
【整体算法思路】
步骤1：读取输入并完成初始化。
目的：将题目数据转换为可计算的状态。
步骤2：建立本题需要的数据结构/状态定义。
目的：为后续核心算法提供正确的信息组织方式。
步骤3：执行核心算法流程（见下方关键函数或循环）。
目的：按题意逐步求解并得到最终答案。
步骤4：输出结果并结束程序。
目的：返回题目要求的结果，完成一次完整求解。
*/

//ÿڵǺڼ
//ڵǺɫ
//Ҷڵ㣨NIL)Ǻɫ
//ڵӽڵǺɫ
//Ӹڵ㵽Ҷڵ·ϣɫڵͬ
// 
// 
//··ֵΪ2̣ȫɫں
// 
//վ游ڵ㣬ɾվڸڵ㿴ɾ
//·Ϻɫڵȿ֪ĽڵΪɫʧ⣬ɫܻʧ⣬Ϊɫӽڵ㲻Ϊɫʧ
//ǰÿ·ĺɫڵܸı
//1ӽڵ븸ڵΪ죬ڵΪɫڵ常ڵΪɫ游ڵ
//2常ڵΪɫLLͣΪں죨ɫϸߺںڣɫ³
//3,LRƣСRRRLȼ
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct Node
{
	int key, color;//0:ɫ 1ɫ 2˫غ
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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

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

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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
Node* insert_maintain(Node* root)//
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
	root->color = 1;//ϴ˴ߵΪ˫غ
	return root;
}
Node* _erase(int key, Node* root)
{
	if (root == &NIL)return root;
	if (key < root->key)root->left = _erase(key, root->left);
	else if(key > root->key)root->right = _erase(key, root->right);
	else
	{
		if (root->left == &NIL || root->right == &NIL)//һӽڵ0ӽڵ,һNILڵΪɫʱwuڵ
		{
			Node* temp = (root->left != &NIL) ? root->left : root->right;
			temp->color+= root->color;//ӽڵڵɫΪڵٸڵ
			//ΪڣӱΪNIL->ڻ˫غڣΪ죬ΪNIL  
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
	//ֵܽڵΪɫ
	if (has_red_node(root))
	{
		root->color = 0;//ɵĽڵΪɫ
		if (root->left->color == 0)
		{
			root = right_rotated(root);//˽ڵ㲻һλΪұ˫غiٻһɫ
			root->right = erase_maintain(root->right);

		}
		else
		{
			root = left_rotated(root);//˽ڵ㲻һλΪұ˫غiٻһɫ
			root->left = erase_maintain(root->left);
		}
		root->color = 1;//µĽڵΪɫ
		return root;
	}
	if ((root->left->color == 2 && !has_red_node(root->right))|| (root->right->color == 2 && !has_red_node(root->left)))//1
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