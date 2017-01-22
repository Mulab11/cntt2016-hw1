
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
double low[N], high[N];
PI p[N];
int r[N];
inline PI operator - (const PI &a, const PI &b){ return MP(a.FT - b.FT, a.SC - b.SC); }
inline double dis(const PI &a){ return sqrt(a.FT * a.FT + a.SC * a.SC); }

class CandyOnDisk  
{  
        public:  
        void update(int x, double L, double H){ cmin(low[x], max(L, 0.0)), cmax(high[x], min(H, (double)r[x])); }
        string ableToAchieve(vector <int> x, vector <int> y, vector <int> R, int sx, int sy, int tx, int ty)  
        {  
        	 int n = x.size();
			 PI S = MP(sx, sy), T = MP(tx, ty);
        	 FOR(i, n) p[i] = MP(x[i], y[i]);
        	 FOR(i, n) r[i] = R[i];
        	 FOR(i, n) low[i] = inf, high[i] = 0;
			 FOR(i, n) if (dis(S - p[i]) <= r[i]) low[i] = high[i] = dis(S - p[i]);
			 //不难发现我们每个圆盘能到达的部分一定是一段区间，然后我们不妨用bellman-ford对其更新。 
			 FOR(NUM, n)
			 	FOR(i, n) FOR(j, n) if (p[i] != p[j] && low[i] < inf){ //注意，如果发现转盘的中心重叠，那么则不能更新。 
			 		double D = dis(p[i] - p[j]);
			 		if (D <= r[j] - r[i]) low[i] = 0, update(j, D - high[i], D + high[i]);
			 		if (low[i] <= D + r[j] && D - r[j] < high[i])
					 	if (D <= r[i] - r[j]) update(i, D - r[j], D + r[j]), update(j, 0, r[j]);
					 	else update(i, D - r[j], D + r[j]), update(j, D - r[i], D + r[i]);
				}
			FOR(i, n) if (dis(T - p[i]) >= low[i] && dis(T - p[i]) <= high[i]) return "YES";
			if (S == T) return "YES";
			return "NO";
        }  
        
};  

