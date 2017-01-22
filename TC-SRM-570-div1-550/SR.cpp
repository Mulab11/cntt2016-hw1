
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

const int N = 36 + 5;
int hd[N], fa[N], q[N], sz[N], tail;
LL f[N][N][N][2], g[N][N][2];
struct Edge{ int nxt, to; } e[N * 2];

void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
void bfs(int x){
	int l, r;
	for( fa[q[l = r = 1] = x] = 0; l <= r; x = q[++l])
		DFOR(i, x, y) if (fa[x] != y) fa[q[++r] = y] = x;
}
class CentaurCompany  
{  
        public:  
        double getvalue(vector <int> a, vector <int> b)  
        {  
        	//答案只和选到的联通块个数和点数有关，所以考虑树形dp 
        	tail = 0;
        	MEM(sz, 0), MEM(fa, 0), MEM(f, 0), MEM(hd, 0);
        	int n = a.size() + 1;
        	FOR(i, n - 1) add(a[i], b[i]), add(b[i], a[i]);
        	bfs(1);
        	REP(i, 0, n) f[i][0][0][0] = f[i][0][1][1] = 1;
        	REP(i, 0, n) sz[i] = 1;
        	PER(now, n, 1){
        		int y = q[now], x = fa[y];
        		MEM(g, 0);
				REP(i, 0, sz[x]) REP(j, 0, sz[x]) REP(k, 0, sz[y]) REP(l, 0, sz[y]){
					g[i + k][j + l][0] += f[x][i][j][0] * (f[y][k][l][0] + (k > 0 ? f[y][k - 1][l][1] : 0));
					g[i + k][j + l][1] += f[x][i][j][1] * (f[y][k][l][0] + f[y][k][l][1]);
				}
				sz[x] += sz[y];
				memcpy(f[x], g, sizeof g);
			}
			int y = 0;
			double ans = 0;
			REP(i, 0, n) REP(j, 0, n) ans += f[0][i][j][0] * max(2 * i - j - 2, 0);
			FOR(i, n - 1) ans /= 2;
			return ans;
        }  

};  


