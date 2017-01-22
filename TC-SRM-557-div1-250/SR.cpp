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
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
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
  
  
class FoxAndMountainEasy  
{  
        public:  
        string possible(int n, int h0, int hn, string history)  
        {  
        	int h = h0, Low = h0; 
        	VEP(i, history) if (history[i] == 'U') ++h; else --h, cmin(Low, h);//计算最低值。 
        	hn -= h;
        	n -= history.size();
        	if (Low < 0) hn += Low, n += Low;//如果最低值小于0需要在前面补上U 
        	return ((hn & 1) ^ (n & 1)) == 0 && abs(hn) <= n ? "YES" : "NO";
        }    
};  

