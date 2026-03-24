/*
【题目】4 Letcode 130 围绕的区域
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

//ΧƵ
class unionset {
public:
    vector<int>fa;
    unionset(int n) :fa(n + 1) {
        for (int i = 0;i <= n;i++)
        {
            fa[i] = i;
        }
    }
    int find(int a)
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

        if (fa[a] == a)return a;
        fa[a] = find(fa[a]);

        // 步骤4（代码实现）：输出结果并返回。
        // 目的：给出最终答案并结束程序执行。
        // 实现：调用输出语句打印结果，并通过 return 结束流程。
        return fa[a];
    }
    int merge(int a, int b)
    {
        int aa = find(a), bb = find(b);
        if (aa == bb)return 0;
        fa[aa] = bb;
        return 1;
    }
};
class Solution {
public:
    /*void find(int(*num)[200],vector<vector<char>>& board,int x,int y,int l,int w)
    {
        num[x][y]=1;
        if(x+1<l && !num[x+1][y]&&board[x+1][y]=='O')
        {
            find(num,board,x+1,y,l,w);
        }
         if(x-1>=0&&!num[x-1][y]&&board[x-1][y]=='O')
        {
            find(num,board,x-1,y,l,w);
        }
         if(y+1< w && !num[x][y+1] && board[x][y+1]=='O')
        {
            find(num,board,x,y+1,l,w);
        }
         if(y-1>=0 &&!num[x][y-1]&&board[x][y-1]=='O')
        {
            find(num,board,x,y-1,l,w);
        }
    }*/
    void solve(vector<vector<char>>& board) {
        /*int n=board.size();
        int m=board[0].size();
        int num[200][200]={0};
        for(int x=0;x<n;x++)
        {
        if(board[x][0]=='O')
        find(num,board,x,0,n,m);
         if(board[x][m-1]=='O')
        {
        find(num,board,x,m-1,n,m);
        }
        }
        int m_=m-1;
        for(int y=1;y<m_;y++)
        {
            if(board[0][y]=='O')
            find(num,board,0,y,n,m);
            if(board[n-1][y]=='O')
            {
            find(num,board,n-1,y,n,m);
            }
        }
        for(int x=0;x<n;x++)
        {
            for(int y=0;y<m;y++)
            {
                if(!num[x][y])
                board[x][y]='X';
            }
        }*/
        int n = board.size();
        if (n == 0)return;
        int m = board[0].size();
        unionset s(n * m);
        for (int i = 0;i < n;i++)
        {
            for (int j = 0;j < m;j++)
            {
                int ind = i * m + j + 1;
                if (board[i][j] == 'O')
                {
                    if (i == 0 || i == n - 1)s.merge(ind, 0);
                    if (j == 0 || j == m - 1) s.merge(ind, 0);
                    if (j + 1 < m && board[i][j + 1] == 'O') s.merge(ind, 1 + ind);
                    if (i + 1 < n && board[i + 1][j] == 'O') s.merge(ind, ind + m);
                }
            }
        }
        for (int i = 0;i < n;i++)
        {
            for (int j = 0;j < m;j++)
            {
                int ind = i * m + j + 1;
                if (board[i][j] == 'O' && s.find(ind) != s.find(0))board[i][j] = 'X';
            }
        }
    }
};
/*ʱֻҪͨ
Ȧһ㶼O
