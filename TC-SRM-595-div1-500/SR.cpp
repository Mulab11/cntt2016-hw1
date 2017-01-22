
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
  
const int N = 2500 + 5;
int L[N], R[N], suf[N], pre[N], f[N], g[N][N];
class LittleElephantAndRGB  
{  
        public:  
        long long getNumber(vector <string> list, int m)  
        {  
        	MEM(pre, 0), MEM(suf, 0), MEM(L, 0), MEM(R, 0), MEM(g, 0);
        	
        	string a = " ";
        	VEP(i, list) a += list[i];
        	int n = a.size() - 1;
        	//L，R分别表示向左向右连续的G的个数 
        	L[0] = 0;
        	REP(i, 1, n) L[i] = a[i] == 'G' ? L[i - 1] + 1 : 0;
        	R[n + 1] = 0;
        	PER(i, n, 1) R[i] = a[i] == 'G' ? R[i + 1] + 1 : 0;
        	
        	//pre，suf表示从当前位置到pre，suf对应的位置，就至少拥有一个连续的m个'G'的串。 
        	pre[0] = 0;
        	REP(i, 1, n) pre[i] = L[i] >= m ? i - m + 1 : pre[i - 1];
        	suf[n + 1] = n + 1;
        	PER(i, n, 1) suf[i] = R[i] >= m ? i + m - 1 : suf[i + 1];
        	
        	//f[i]表示从i~n可以拿出多少个子串，里面至少包含一个连续的m个'G'的串。 
        	f[n + 1] = 0;
        	PER(i, n, 1) f[i] = f[i + 1] + (n + 1 - suf[i]);
				
			//g[i][j]表示从i~n可以拿出多少个不包含连续的m个'G'的串，且开头至少含有j个'G'的串 
			PER(i, n, 1){
				REP(j, 1, min(R[i] - 1, m - 1)) g[i][j] = 1;	
				if (R[i] < m) g[i][R[i]] = suf[i] - i - R[i] + 1;
				PER(j, m - 1, 1) g[i][j] += g[i][j + 1];
				REP(j, 1, m - 1) g[i][j] += g[i + 1][j];
			}
        	
        	//然后我们就可以枚举a和b然后直接计算合法的cd数目。 
        	LL ans = 0;
        	REP(i, 1, n - 1) REP(j, i, n - 1)
        		if (i <= pre[j]) ans += LL(n - j) * (n - j + 1) / 2;
        		else ans += f[j + 1] + g[j + 1][m - min(L[j], j - i + 1)];
        	
			return ans;        		
        }  
  
};  

