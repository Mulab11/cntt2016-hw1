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

int f[50 + 5];
bool judge(LL x){
	if (x == 1) return 1;
	if (x % 5 || x == 0) return 0;
	return judge(x / 5);
}
class CuttingBitString  
{  
        public:  
        int getmin(string S)  
        {  
        	int n = S.size();
        	MEM(f, 0x3f), f[0] = 0;
        	REP(i, 1, n){
        		LL s = 0, pw = 0;
				PER(j, i - 1, 0){
					s += LL(S[j] - '0') << pw++;
        			if (judge(s) && S[j] == '1') cmin(f[i], f[j] + 1);
        		}
        	}
        	return f[n] == inf ? -1 : f[n];
        }  
};  

