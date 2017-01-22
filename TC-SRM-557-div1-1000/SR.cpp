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
  
const int N = 1000 + 5;
LL a[N];

class XorAndSum  
{  
        public:  
        long long maxSum(vector<long long> number)  
        {  
        	int now = 1, n = number.size();
        	REP(i, 1, n) a[i] = number[i - 1];
        	//高斯消元求线性基 
        	PER(j, 63, 0){
        		int k = 0;
				REP(i, now, n) if (a[i] >> j & 1) {k = i; break;}
				if (!k) continue; else swap(a[now], a[k]);
				REP(i, 1, n) if (i != now && a[i] >> j & 1) a[i] ^= a[now];
				++now;
			}
			
			LL sum = 0;
			REP(i, 2, n) a[1] ^= a[i];
			REP(i, 2, n) sum += a[i] ^ a[1];
			sum += a[1];
			return sum;
        }  
};  

