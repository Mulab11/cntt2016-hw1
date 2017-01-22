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
const int inf = 0x3f3f3f3f;
const int MOD = 1000000007;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 1000 + 5;
int f[N];

class Stamp  
{  
        public:  
        int getMinimumCost(string S, int SC, int PC)  
        {  
        	int n = S.size();
			LL ans = (LL)inf * inf;
        	REP(L, 1, n){//枚举长度 
        		MEM(f, 0x3f);
        		f[0] = 0;
        		REP(i, 1, n){
        			char ch = '*';
        			PER(j, i - 1, 0) if (S[j] == '*' || S[j] == ch || ch == '*'){
        				if (S[j] != '*') ch = S[j];
        				if (i - j >= L) cmin(f[i], f[j] + (i - j - 1) / L + 1);//转移 
					} else break;
				}
				cmin(ans, (LL)SC * L + (LL)PC * f[n]);
			}
			return (int)ans;
        }  
};  
