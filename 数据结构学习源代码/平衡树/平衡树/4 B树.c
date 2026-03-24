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
	// 步骤1（代码实现）：读取输入并完成必要初始化。
	// 目的：把原始输入转化为程序可处理的数据状态。
	// 实现：通过输入语句与初始赋值准备基础变量。
	// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
	// 目的：为核心转移/搜索/计算过程提供载体。
	// 实现：用数组、容器或自定义结构存储中间状态与关系。
	// 步骤3（代码实现）：执行核心算法流程。
	// 目的：按照题意完成状态转移、搜索或计算求解。
	// 实现：通过循环、递归或转移方程推进计算直到得到答案。

	srand(time(NULL));
	Node* root = NULL;
	for (int i = 0;i < 15;i++)
	{
		int key = rand() % 100;
		root = insert(root, key);
		printf("insert %d\n", key);
		output(root);
	}
	int x = 0;
	printf("\n");
	while (~scanf_s("%d", &x))
	{
		erase(root, x);
		output(root);
		printf("\n");
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
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