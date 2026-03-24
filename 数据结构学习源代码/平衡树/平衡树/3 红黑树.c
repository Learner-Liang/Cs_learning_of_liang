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
// 步骤1（代码实现-输入与边界）：先读取题目输入，并明确变量含义与取值范围。
// 目的：让后续每个状态/循环都建立在正确输入之上，避免越界与未初始化。
// 关键代码说明：紧随其后的 cin/scanf 语句负责读入 n、m、权值、边信息等原始数据。
// 步骤2（代码实现-状态定义与初始化）：构建 dp/图/数组/容器等数据结构并设置初值。
// 目的：把“题意”翻译成“可计算状态”，并给转移提供合法起点（如 0、INF、初始答案）。
// 关键代码说明：常见初始化语句（memset、赋初值、清空容器）决定了后续转移是否正确。
// 步骤3（代码实现-核心转移/搜索）：在循环或递归中执行状态更新，逐步逼近最优解/可行解。
// 目的：把局部决策累积为全局答案；若是 DP，本质是“已知子问题 -> 当前问题”的转移。
// 关键代码说明：max/min/松弛/合并等更新语句是核心；它们对应题目中的数学关系或最优性原理。

	init_NIL();
	srand(time(NULL));
	Node* root = &NIL;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;i < 100;i++)
	{
		int key = rand() % 150;
		root=_insert(root, key);
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		printf("insert %d\n", key);
		output(root);
	}
	printf("\n");
	int x;
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	while (~scanf_s("%d", &x))
	{
		if (x == -1)break;
		root = erase(x, root);
		output(root);
		printf("\n");
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
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
			// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
			// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

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