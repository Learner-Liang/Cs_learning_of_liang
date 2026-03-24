#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
////分裂出节点
///*
//m阶B树
//1，每个节点最多有m棵子树
//2，若根节点不是叶子节点至少两颗子树 ，范围为1到m-1
//3，除了根节点之外，非终端节点至少m/2（向上取整）棵子树
//4，如果一个节点有n-1个关键字，该节点有n个分支，且n-1个关键字按照递增排列
//5，叶子节点再同一层
//6，非根节点中关键字的个数n满足【M/2】-1《=n<=m-1平衡条件按核心
//*/
////插入调整，插入调整站在父节点进行处理，发生在节点关键字达到m时候，操作：节点分裂（中间节点上溢）
#define m 5
//五阶
typedef struct Node {
	int n;//表示当前节点存储的关键词的数量
	int key[m+1];//m-1个关键字
	struct Node* next[m+1];
}Node;
Node* getNewNode();//得到新节点
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
	if (root->n == m)//root为带分裂的节点
	{
		Node* p = getNewNode();//从父节点对其进行调整
		p->next[0]=root;
		root = insert_maintain(p, root, 0);
	}
	return root;
}
Node* __insert(Node *root,int key)//从第一个插入开始思考，第一个节点插满之后分裂出第二个，从终端开始插入，
//因而第一个节点为空则空，不存在第一个节点为空，其余还有节点的的情况
//除此之外，若是不是终端，root->next[0] == NULL，则任意一个关键词旁边一定有节点
{
	if (root == NULL||root->next[0] == NULL)//插入终端，没有子树或者当前树为空
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
		root->key[i] = root->key[i - 1];//root为终端，底部都为空节点
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
Node* erase(Node* root,int key)//删除调整：在父节点处理：某个子节点关键字节点为【m/2]-2
//进行左旋，右旋，合并
// 下溢：兄弟节点的一个关键字移，父节点的关键字下移，借的关键字的节点挂到借的父节点的关键字上（与左旋类似）跟左右的兄弟节点借
// 兄弟节点无则直接合并：与父节点借
//终端直接删除，非终端找到前驱或者后继
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
	if (root->next[0] == NULL)//终端
	{
		if (key == root->key[pos]) erasepos(root, pos);
		return root;
	}
	//非终端
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