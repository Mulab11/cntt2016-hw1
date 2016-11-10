# Suminator

作者：沈睿

关键词：暴力、分类讨论、栈

## 题目简述

给你一个数栈，初始里面有无穷多个$$0$$。对于一个包含$$n$$个非负整数操作序列$$program$$，将会依次对这个栈进行操作。

$$1.$$如果当前的数大于$$0$$，就把该数压进栈里。

$$2.$$如果当前的数为$$0$$，那么就把栈顶两个数弹出，并把这两个数的和压进栈里。

由于一些信息缺失，给你的操作序列里面**有且仅有**一个数是未知的，用$$-1$$表示，它可以是任意非负整数。现在告诉你所有操作结束后栈顶的数$$wantedResult$$，问你未知数解的情况（无解，一个解，或无穷解）

数据范围：$$1\le n\le 50,-1\le program_{i}\le 10^{9},1\le wantedResult\le 10^{9}$$

## 题解

我们不妨进行分类：

$$1.$$**未知数为0。** 那我们模拟压栈弹栈的过程即可得到未知数是否为0。

$$2.$$**未知数不为0。** 不难发现栈顶的数是一些数的和，那我们模拟压栈弹栈的过程便可得到哪些数相加组成了最后的答案，最终得到这样一个方程$$ax=b(a=0/1)$$。那么剩下的就是解一元一次方程的事情了（~~小学生都会~~）。关于$$a$$的系数，我们又可以做如下分类：

$$(1)$$ $$a=0$$，那么如果$$b=0$$便无穷解，$$b\neq 0$$便无解。

$$(2)$$ $$a=1$$，那么$$a$$有唯一解，而且$$a=b$$。

该算法的时间复杂度与空间复杂度均为$$O(n)$$。

## 代码

```C++
#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7fffffff;
const int MOD = 1000000007;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }


class Suminator  
{  
        public:  
        int findMissing(vector <int> program, int wantedResult)  
        {  
            reverse(program.begin(), program.end());

            int cnt, found = 0; LL tot;
            
            cnt = 1, tot = 0;            
            RUN(i, program){
                if (*i == 0 || *i == -1) ++cnt;
                else if (--cnt >= 0) tot += *i;
                if (cnt == 0) break;
            }
            if (tot == wantedResult) return 0;
            
            //unknown number = 0 
            cnt = 1, tot = 0;
            RUN(i, program){
                if (*i == 0) ++cnt;
                else if (--cnt >= 0) if (*i > 0) tot += *i; else found = 1;
                if (cnt == 0) break;
            }
            
            //unknown number != 0
            LL x = wantedResult - tot;
            if (!found)//the coefficient of unknown number = 0 
                if (x) return -1;
                else return 1;
            else//the coefficient of unknown number = 1
                if (x >= 1 && x <= 1000000000) return x;
                else return -1;
        }  
};  
```

