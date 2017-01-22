
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
const int MOD = 1000000009;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }

const int N = 1000000 + 5;
int P[N], tot;
pair<int, char> tmp[N];

void make(LL x, int W){//预处理出所有因数塞进数组P里面 
	for (LL i = 1; i * i <= x; i++) if (!(x % i)){
		if (i <= W) P[++tot] = i;
		if (x / i <= W) P[++tot] = x / i;
	}
}
int pw(int x, int k){ int s = 1; for(; k; k >>= 1, x = (LL)x * x % MOD) if (k & 1) s = (LL)s * x % MOD; return s;}//快速幂 
int Sum(int x, int L, int R){ return (LL)(pw(x, R + 1) - pw(x, L) + MOD) * pw(x - 1, MOD - 2) % MOD; }//等比数列求和 
class CharacterBoard
{  
        public:  
        int countGenerators(vector <string> a, int W, int i0, int j0)//i0和j0是没有意义的因为这样只会导致不合法。 
        {  
        	int n = a.size(), m = a[0].size();
        	tot = 0;
        	
        	//与处理出所有因数并且unique 
			FOR(i, n) REP(j, -m + 1, m - 1) if ((LL)i * W + j > 0) make((LL)i * W + j, W);
			sort(P + 1, P + tot + 1);
			tot = unique(P + 1, P + tot + 1) - P - 1;
			//计算理想情况下的所有答案			
			int ans = 0;
			if (W >= n * m) ans = (ans + Sum(26, 0, W - n * m)) % MOD;
			//特殊因数单独计算 
			REP(i, 1, tot){
				if (P[i] >= n * m) ans = (ans - pw(26, P[i] - n * m) + MOD) % MOD;
				int tot = 0;
				FOR(x, n) FOR(y, m) tmp[++tot] = MP(int(((LL)x * W + y) % P[i]), a[x][y]);
				sort(tmp + 1, tmp + tot + 1);
				int cnt = 0, bad = 0;
				REP(j, 2, tot)
					if (tmp[j].FT == tmp[j - 1].FT){
						if (tmp[j].SC != tmp[j - 1].SC){ bad = 1; break; }//出现矛盾情况 
						++cnt;//出现重复 
					}
				if (!bad) ans = (ans + pw(26, P[i] - n * m + cnt)) % MOD;
			}
			return ans;
        }  

};  
  

