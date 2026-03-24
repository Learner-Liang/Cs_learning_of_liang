/*
【题目】3,最长子序列（非连续）
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

class unionset {
// 步骤1（代码实现）：读取输入并完成必要初始化。
// 目的：把原始输入转化为程序可处理的数据状态。
// 实现：通过输入语句与初始赋值准备基础变量。
// 步骤2（代码实现）：构建本题使用的数据结构或状态表示。
// 目的：为核心转移/搜索/计算过程提供载体。
// 实现：用数组、容器或自定义结构存储中间状态与关系。
// 步骤3（代码实现）：执行核心算法流程。
// 目的：按照题意完成状态转移、搜索或计算求解。
// 实现：通过循环、递归或转移方程推进计算直到得到答案。

public:
    int n;
    vector<int>fa, size;
    unionset(int n) :fa(n + 1), size(n + 1) {
        this->n = n;
        for (int i = 0;i <= n;i++)
        {
            fa[i] = i;
            size[i] = 1;
        }
    }
    int find(int a)
    {
        if (fa[a] == a)

// 步骤4（代码实现）：输出结果并返回。
// 目的：给出最终答案并结束程序执行。
// 实现：调用输出语句打印结果，并通过 return 结束流程。
return a;
        fa[a] = find(fa[a]);
        return fa[a];
    }
    int merge(int a, int b)
    {
        int aa = find(a), bb = find(b);
        if (aa == bb)return 0;
        if (size[aa] > size[bb])
        {
            size[aa] += size[bb];
            fa[bb] = aa;
        }
        else
        {
            size[bb] += size[aa];
            fa[aa] = bb;
        }
        return 1;
    }
    int Max()
    {
        int ans = 0;
        for (int i = 0;i < n;i++)
        {
            ans = max(ans, size[i]);
        }
        return ans;
    }
};
class Solution {
public:

    int longestConsecutive(vector<int>& nums) {
        /*set<int>p(nums.begin(),nums.end());
        int temp=0,ans=0;
        int last;
        if(!p.empty())
        {
           temp=1;
       last=*p.begin();
        p.erase(p.begin());
        }
       while(!p.empty())
        {
           int temp1=*p.begin();
           if(temp1==last+1)
           {
               temp++;
           }
           else
           {
               ans=max(ans,temp);
               temp=1;
           }
           last=temp1;
            p.erase(p.begin());
        }
        ans=max(ans,temp);
        return ans;*/
        unionset s(nums.size());
        map<int, int>m;
        int cnt = 0;
        for (int i = 0;i < nums.size();i++)
        {
            if (m.find(nums[i]) != m.end()) continue;
            m[nums[i]] = cnt++;
            if (m.find(nums[i] - 1) != m.end()) s.merge(m[nums[i] - 1], m[nums[i]]);
            if (m.find(nums[i] + 1) != m.end()) s.merge(m[nums[i] + 1], m[nums[i]]);
        }
        return s.Max();
    }
};





class Unionset
{
public:
    Unionset(int n) :p(n + 1)
    {
        for (int i = 0;i <= n;i++)
            p[i] = i;
    }
    int find(int x)
    {
        return p[x] = (p[x] == x ? x : find(p[x]));
    }
    void merge(int x, int y)
    {
        int xx = find(x), yy = find(y);
        p[xx] = yy;
    }
    vector<int>p;
};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int k = m * n;
        Unionset s(k);
        for (int i = 0;i < m;i++)
        {
            for (int j = 0;j < n;j++)
            {
                if (grid[i][j] == '0')continue;
                int ind = i * n + j + 1;
                if (j + 1 < n && grid[i][j + 1] == '1')s.merge(ind, ind + 1);
                if (i + 1 < m && grid[i + 1][j] == '1')s.merge(ind, ind + n);
            }
        }
        int count = 0;
        for (int i = 0;i < m;i++)
        {
            for (int j = 0;j < n;j++)
            {
                int ind = i * n + j + 1;;
                if (grid[i][j] == '1' && (s.find(ind) == ind))count++;
            }
        }
        return count;
    }
};