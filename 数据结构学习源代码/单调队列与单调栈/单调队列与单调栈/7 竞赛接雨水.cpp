#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;
//Ω””ÍÀÆ 
class Solution {
public:
    int trap(vector<int>& height) {
        stack<int>s;
        int n = height.size(), ans = 0;
        for (int i = 0;i < n;i++)
        {
            while (!s.empty() && height[s.top()] < height[i])
            {
                int h = height[s.top()];
                s.pop();
                if (s.empty())break;
                ans += (min(height[s.top()], height[i]) - h) * (i - 1 - s.top());
            }
            s.push(i);
        }
        return ans;
    }
};
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, n = height.size();
        deque<int>q;
        int i = 0;
        for (;i < n;i++)
        {
            if (!q.empty() && height[i] >= height[q.front()])
            {
                int j = q.front(), k = height[q.front()];
                while (j < i)
                {
                    ans += k - height[j];
                    j++;
                }
            }
            while (!q.empty() && height[i] >= height[q.back()])q.pop_back();
            q.push_back(i);
        }
        int head = q.front(), tail;
        while (!q.empty())
        {
            q.pop_front();
            if (!q.empty())
            {
                tail = q.front();
                while (head < tail)
                {
                    head++;
                    ans += height[tail] - height[head];
                }
            }

        }
        return ans;
    }
}; 