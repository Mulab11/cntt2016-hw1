
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
LL c[N][N], f[N][N];
int sum[N];
vector<int> a[N];
class Excavations  
{  
        public:  
        long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)  
        {  
        	int n = kind.size(), m = found.size(); 
        	FOR(i, m + 1) a[i].clear();
        	FOR(i, n) FOR(j, m + 1) if (j == m || kind[i] == found[j]) {a[j].PB(depth[i]); break; }
        	FOR(j, m + 1) sort(a[j].begin(), a[j].end());
        	MEM(c, 0);
			FOR(i, N) FOR(j, N) c[i][j] = j == 0 ? 1 : c[i - 1][j] + c[i - 1][j - 1];
			REP(i, 1, m) sum[i] = sum[i - 1] + a[i - 1].size();
        	LL ans = 0;
        	//枚举选取的不包含found的种类的建筑的最低深度。 
        	VEP(now, a[m]){
        		int dep = a[m][now];
        		MEM(f, 0), f[0][0] = 1;
        		FOR(i, m) REP(j, 0, sum[i]) if (f[i][j] > 0)
        			VEP(k, a[i]) if (a[i][k] < dep) f[i + 1][j + a[i].size() - k - 1] += f[i][j];
        		REP(j, 0, sum[m]) ans += c[j + a[m].size() - now - 1][K - m - 1] * f[m][j];
			}
			//没有选取不包含found种类的建筑的情况。 
			MEM(f, 0), f[0][0] = 1;
        	FOR(i, m) REP(j, 0, sum[i]) if (f[i][j] > 0)
        		VEP(k, a[i]) if (a[i][k] < inf) f[i + 1][j + a[i].size() - k - 1] += f[i][j];
        	REP(j, 0, sum[m]) ans += c[j][K - m] * f[m][j];
			return ans;
        }  

};  

