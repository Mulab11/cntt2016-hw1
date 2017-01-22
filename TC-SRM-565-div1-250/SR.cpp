
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
  
const int N = 100 * 2;
LL f[N][N];
class MonstersValley  
{  
        public:  
        int minimumPrice(vector<long long> d, vector <int> p)  
        {  
        	//dp状态f[i][j]表示到第i个怪物，受到j点伤害可以获得的智商，如果为-1表示你无法只收到j点伤害通过第j个生物 
        	int n = d.size();
        	MEM(f, -1);
        	REP(i, 0, n * 2) f[0][i] = 0;
        	REP(i, 0, n - 1) REP(j, 0, n * 2) if (~f[i][j]){
        		cmax(f[i + 1][j + p[i]], f[i][j] + d[i]);
      			if (f[i][j] >= d[i]) cmax(f[i + 1][j], f[i][j]); 
			}
			REP(i, 0, n * 2) if (f[n][i] > -1) return i;
        }  
     
};  

