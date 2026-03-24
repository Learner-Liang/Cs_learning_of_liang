class unionset {
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
        if (fa[a] == a)return a;
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