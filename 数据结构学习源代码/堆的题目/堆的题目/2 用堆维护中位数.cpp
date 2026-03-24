#include <iostream>
#include <set>
#include <queue>
using namespace std;
class MedianFinder {
public:
    int tot = 0;
    typedef pair<int, int>p;
    set<p>s1, s2;
    MedianFinder() {
        tot = 0;
    }

    void addNum(int num) {
        if (tot % 2)
        {
            if (!s2.empty() && s2.begin()->first < num)
            {
                s1.insert(p{ -(s2.begin()->first), s2.begin()->second});
                s2.erase(s2.begin());
                s2.insert(p{ num,tot++ });;
            }
            else
            {
            }
        }
    }

    double findMedian() {
        if ((s1.size() + s2.size()) % 2)return -s1.begin()->first;
        else
        {
            double a = (-s1.begin()->first + s2.begin()->first) / 2.0;
            return a;
        }
    }
};
