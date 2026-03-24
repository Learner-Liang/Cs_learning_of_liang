/*
【题目】11 Ac自动机   
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

#include <iostream>
#include <queue>
using namespace std;
//д洢ǵʣıƥ
//ȼƥָ룬ĬϽڸڵλ
typedef struct Node {
	int flag;
	Node* next[26];
	Node* fail;
	//Ҫʣ˴ӦüһַĶ
}Node;
//һıֵеģʽ
//öģʽֵACԶ
//ƥǰ׺
Node* getNode_ac()
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

	Node* p = (Node*)malloc(sizeof(Node));
	p->flag = 0;
	p->fail = NULL;
	for (int i = 0;i < 26;i++)
	{
		p->next[i] = NULL;
	}

	// 步骤4（代码实现）：输出结果并返回。
	// 目的：给出最终答案并结束程序执行。
	// 实现：调用输出语句打印结果，并通过 return 结束流程。
	return p;
}
void clear_ac(Node* p)
{
	if (p == NULL)return;
	for (int i = 0;i < 26;i++)
	{
		clear_ac(p->next[i]);
	}
	free(p);
}
void insert_ac(Node* root, const char* s)
{
	Node* p = root;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		if (p->next[ind] == NULL)p->next[i] = getNode_ac();
		p = p->next[ind];
	}
	p->flag = 1;
	return;
}
void build_ac(Node* root)
{
	queue<Node*>q;
	for (int i = 0;i < 26;i++)
	{
		if (root->next[i] == NULL)continue;
		root->next[i]->fail=root;
		q.push(root->next[i]);

	}
	while (!q.empty())
	{
		Node* temp = q.front(), * p;
		q.pop();
		for (int i = 0;i < 26;i++)
		{
			if (temp->next[i] == NULL)continue;
			//޸
			/*
			* if(temp==root)temp->next[i]=root;
			* else
			 temp->next[i]=temp->fail->next[i];ǰѾѭ
			 continue;
			*/
			p = temp->fail;
			while (p && p->next[i] == NULL)p=p->fail;//˴Ҳ
			if (p == NULL)p = root;
			else p = p->next[i];
			temp->next[i]->fail = p;
			q.push(temp->next[i]);
		}
	}
}
void find_ac(Node* root, const char* s)
{
	Node* p = root, * q;
	for (int i = 0;s[i];i++)
	{
		int ind = s[i] - 'a';
		while (p && p->next[ind] == NULL)p = p->fail;

		if (p == NULL)p = root;
		else p = p->next[ind];
		//иΪ p = p->next[ind];
		q = p;
		//˴ԼжǷɴﲢַ
	}
}
//Ż
//ֱָҪĿڵ
int main11()
{

	return 0;
}