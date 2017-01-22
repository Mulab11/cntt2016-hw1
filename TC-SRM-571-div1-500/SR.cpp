// BEGIN CUT HERE  
/* 
 
*/  
// END CUT HERE  
#line 7 "MagicMolecule.cpp"  

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
  
const int N = 50 + 5;
int g[N][N], a[N], n, ans;
vector<PI> e;
class MagicMolecule  
{  
        public:  
        //直接暴力我们会发现过程最多只有16条边需要抉择。 
        void dfs(int x, int dep, LL s, int sum){
        	if (3 * (n - dep) < 2 * n) return;
        	if (x >= e.size()) { cmax(ans, sum); return; }
        	int i = e[x].FT, j = e[x].SC;
        	if ((s >> i & 1) && (s >> j & 1)){
        		dfs(x + 1, dep + 1, s ^ (1ll << i), sum - a[i]);
        		dfs(x + 1, dep + 1, s ^ (1ll << j), sum - a[j]);
			} else dfs(x + 1, dep, s, sum);
		}
        int maxMagicPower(vector <int> mP, vector <string> mB)  
        {  
        	e.clear();
        	n = mP.size();
        	ans = -1;
        	int sum = 0;
        	FOR(i, n) sum += (a[i] = mP[i]);
        	FOR(i, n) FOR(j, n) g[i][j] = (mB[i][j] == 'Y');
        	FOR(i, n) REP(j, i + 1, n - 1) if (!g[i][j]) e.PB(MP(i, j));
        	dfs(0, 0, (1ll << n) - 1, sum);
        	return ans;
        }  

};  

