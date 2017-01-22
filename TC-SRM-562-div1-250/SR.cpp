
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
char a[N][N];
int f[N][N];

class PastingPaintingDivOne  
{  
        public:  
        vector<long long> countColors(vector <string> A, int T)  
        {  
        	int n = A.size(), m = A[0].size();
        	vector<LL> ans;
        	FOR(i, 3) ans.PB(0);
        	MEM(a, '.');
        	MEM(f, 0x3f);
        	REP(i, 1, n) REP(j, 1, m) a[i][j] = A[i - 1][j - 1];
        	//每个格子在最后地图上所占面积是min（从(i,j)开始到左上角第一个不是'.'的格子数，T） 。如果在同一个斜对角线上的是最左上角的格子，那么所占面积为T 
        	REP(i, 1, n) REP(j, 1, m) if (a[i - 1][j - 1] == '.') f[i][j] = f[i - 1][j - 1] + 1; else f[i][j] = 1;
        	REP(i, 1, n) REP(j, 1, m) 
				if (a[i][j] == 'R') ans[0] += min(f[i][j], T); else
				if (a[i][j] == 'G') ans[1] += min(f[i][j], T); else
				if (a[i][j] == 'B') ans[2] += min(f[i][j], T);
			return ans;	
        }  
     
};  

