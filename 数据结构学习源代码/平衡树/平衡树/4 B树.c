/*
【题目】4 B树
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

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
////ѳڵ
///*
//mB
//1ÿڵm
//2ڵ㲻Ҷӽڵ ΧΪ1m-1
//3˸ڵ֮⣬ն˽ڵm/2ȡ
//4һڵn-1ؼ֣ýڵn֧n-1ؼְյ
//5Ҷӽڵͬһ
//6Ǹڵйؼֵĸn㡾M/2-1=n<=m-1ƽ
//*/
////վڸڵдڽڵؼִﵽmʱ򣬲ڵѣмڵ磩
#define m 5
//
typedef struct Node {
	int n;//ʾǰڵ洢Ĺؼʵ
	int key[m+1];//m-1ؼ
	struct Node* next[m+1];
}Node;
Node* getNewNode();//õ½ڵ
void clear();
Node* insert();
Node* __insert();
Node* insert_key();
Node* insert_maintain();
void output();
Node* erase();
Node* preNode();
Node* _erase();
Node* erasepos();
Node* erase_maintain();
Node* left_rotated();
Node* merge();
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

	srand(time(NULL));
	Node* root = NULL;
	
	// 步骤3细化（核心循环解释）：该循环按既定顺序遍历状态/结点。
	// 顺序本身通常携带算法约束（如 0/1 背包倒序遍历、最短路按当前最小距离扩展）。
	for (int i = 0;i < 15;i++)
	{
		int key = rand() % 100;
		root = insert(root, key);
		
		// 步骤4细化（输出语句解释）：该语句输出最终答案，代表全部状态计算完成。
		printf("insert %d\n", key);
		output(root);
	}
	int x = 0;
	printf("\n");
	
	// 步骤1细化（输入语句解释）：这一行把原始数据读入变量，定义了问题规模与基础参数。
	// 若输入不完整或变量含义对应错误，后续所有状态转移都会失真。
	while (~scanf_s("%d", &x))
	{
		erase(root, x);
		output(root);
		printf("\n");
	}
	

// 步骤4（代码实现-答案输出）：按照题目要求的格式输出最终结果并结束程序。
// 目的：把计算得到的最优值/可行解返回给评测系统，形成完整求解闭环。
// 关键代码说明：cout/printf 的输出对象必须与题意一致（如最大值、最短路、方案数等）。
return 0;
}
Node* getNewNode()
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->n = 0;
	memset(p->next, 0, sizeof(Node*) * (m+1));
	return p;
}
void clear(Node* root)
{
	if (root == NULL) return root;
	for (int i = 0;i <= root->n ; i++)
	{
		clear(root->next[i]);
	}
	free(root);
	return;
}
Node* insert(Node* root,int key)
{
	root = __insert(root, key);
	if (root->n == m)//rootΪѵĽڵ
	{
		Node* p = getNewNode();//Ӹڵе
		p->next[0]=root;
		root = insert_maintain(p, root, 0);
	}
	return root;
}
Node* __insert(Node *root,int key)//ӵһ뿪ʼ˼һڵ֮ѳڶն˿ʼ룬
//һڵΪգڵһڵΪգ໹нڵĵ
//֮⣬ǲնˣroot->next[0] == NULLһؼԱһнڵ
{
	if (root == NULL||root->next[0] == NULL)//նˣûߵǰΪ
	{
		return insert_key(root, key);
	}
	int pos = 0;
	// 步骤3细化（判断条件解释）：这里的 if/while 条件用于筛掉非法状态或无效分支，只保留满足约束的候选。
	// 为什么这么写：条件成立时才更新/扩展，能保证正确性并避免错误转移；本质是把题目约束翻译成程序判定规则。

	while (pos < root->n && root->key[pos] < key) pos += 1;
	if (pos < root->n && root->key[pos] == key) return root;
	__insert(root->next[pos], key);
	return insert_maintain(root,root->next[pos],pos);
}
Node* insert_key(Node* root,int key)
{
	if (root == NULL) {
		root = getNewNode();
		root->key[(root->n)++] = key;
		return root;
	}
	int pos = 0;
	while (pos < root->n && root->key[pos] < key) pos += 1;
	if (root->key[pos] == key)return root;
	for (int i = root->n;i>pos;i--)
	{
		root->key[i] = root->key[i - 1];//rootΪնˣײΪսڵ
	}
	root->key[pos] = key;
	root->n+=1;
	return root;
}
Node* insert_maintain(Node* root, Node* child, int pos) {
	if (child->n < m) return root;
	int spos = m / 2;
	Node* node1 = getNewNode();
	Node* node2 = getNewNode();
	node1->n = spos;
	node2->n = m- 1 - spos;
	for (int i = 0; i < spos; i++) {
		node1->key[i] = child->key[i];
		node1->next[i] = child->next[i];
	}
	node1->next[spos] = child->next[spos];
	for (int i = 0; i < node2->n; i++) {
		node2->key[i] = child->key[i + spos + 1];
		node2->next[i] = child->next[i + spos + 1];
	}
	node2->next[node2->n] = child->next[child->n];
	for (int i = root->n; i >= pos; i--) {
		root->key[i + 1] = root->key[i];
		root->next[i + 1] = root->next[i];
	}
	root->key[pos] = child->key[spos];
	root->next[pos] = node1;
	root->next[pos + 1] = node2;
	root->n += 1;
	free(child);
	return root;
}
void output(Node* root)
{
	if (root == NULL)return;
	for (int i = 0;i <= root->n;i++)
	{
		output(root->next[i]);
		if(i!=root->n)
		printf("%d  ", root->key[i]);
	}
}
Node* erase(Node* root,int key)//ɾڸڵ㴦ĳӽڵؼֽڵΪm/2]-2
//ϲ
// 磺ֵܽڵһؼƣڵĹؼƣĹؼֵĽڵҵĸڵĹؼϣƣҵֵܽڵ
// ֵܽڵֱӺϲ븸ڵ
//նֱɾնҵǰߺ
{
	root=_erase(root, key);
	if (root->n == 0)
	{
		Node* temp = root->next[0];
		free(root);
		root = temp;
	}
	return root;
}
Node* preNode(Node* root,int pos)
{
	Node* temp = root->next[pos];
	while (temp->next[temp->n])
		temp = temp->next[temp->n];
	return temp;
}
Node* _erase(Node* root, int key)
{
	if (root == NULL)return root;
	int pos = 0;
	while (pos < root->n && root->key[pos] < key)pos++;
	if (root->next[0] == NULL)//ն
	{
		if (key == root->key[pos]) erasepos(root, pos);
		return root;
	}
	//ն
	if (key == root->key[pos])
	{
		Node* temp = preNode(root,pos);
		root->key[pos] = temp->key[temp->n - 1];
		root->next[pos] = _erase(root->next[pos], temp->key[temp->n - 1]);
	}
	else 
	{
		root->next[pos] = _erase(root->next[pos], key);
	}
	return erase_maintain(root, pos);
}
Node* erasepos(Node* root,int pos)
{
	for (int i = pos+1;i <
	root->n;i++)
	{
		root->key[i-1] = root->key[i];
	}
	root->n -= 1;
	return root;
}
Node* erase_maintain(Node* root,int pos)
{
	int low_line = (m + 1) / 2 - 1;
	if (root->next[pos]->n >= low_line)return root;
	if ((pos >0) && (root->next[pos - 1]->n - 1 > low_line))
	{
		//right_rotated(root, pos - 1);
		for (int i =  root->next[pos]->n;i>0;i--)
		{
			root->next[pos]->next[i] = root->next[pos]->next[i - 1];
			root->next[pos]->key[i] = root->next[pos]->key[i - 1];
		}
		root->next[pos]->n++;
		root->next[pos]->key[0] = root->key[pos - 1];
		root->key[pos - 1] = root->next[pos - 1]->key[root->next[pos - 1]->n-1];
		root->next[pos]->next[0] = root->next[pos - 1]->next[root->next[pos - 1]->n];
		root->next[pos - 1]->next[root->next[pos - 1]->n--] == NULL;
	}
	else if (pos - 1 >= 0 && (root->next[pos - 1]->n - 1 > low_line))
	{
		left_rotated(root, pos);
	}
	else {
		if (pos > 0)merge(root, pos - 1);
		else merge(root, pos);
	}
	return root;
}
Node* left_rotated(Node* root,int pos)
{
	root->next[pos]->key[root->next[pos]->n++] = root->key[pos];
	root->key[pos] = root->next[pos+1]->key[0];
	root->next[pos]->next[root->next[pos]->n] = root->next[pos + 1]->next[0];
	for (int i =1;i<= root->next[pos+1]->n;i++)
	{
		root->next[pos+1]->next[i-1] = root->next[pos+1]->next[i];
		root->next[pos+1]->key[i-1] = root->next[pos+1]->key[i];
	}
	root->next[pos + 1]->next[root->next[pos + 1]->n--] = NULL;
}
Node* merge(Node* root,int pos)
{
	Node* p = getNewNode();
	int val = root->next[pos]->n;
	p->n = val;
	for (int i = 0;i <= val;i++)
	{
		p->next[i] = root->next[pos]->next[i];
		p->key[i] = root->next[pos]->key[i];
	}
	p->key[val++] = root->key[pos];
	p->n++;
	p->n += root->next[pos + 1]->n;
	for (int i = val;i <= p->n;i++)
	{
		p->next[i] = root->next[pos]->next[i-val];
		p->key[i] = root->next[pos]->key[i-val];
	}
	free(root->next[pos]);
	free(root->next[pos + 1]);
	for (int i = pos;i < root->n;i++)
	{
		root->next[i] = root->next[i + 1];
		root->key[i] = root->key[i + 1];

	}
	root->next[pos] = p;
	root->n--;
	return root;
}