
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
  
const int N = 50 + 5, K = 64;
int X[N], Y[N], R[N], ban[N][K], q[N], hd[N], tail = 0, fa[N], sum[N], sg[N];
struct Edge{ int nxt, to; } e[N];
class CirclesGame  
{  
        public:  
        int sqr(int x){ return x * x; }
        void add(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
        void bfs(int x){
        	int l, r;
        	for (q[l = r = 0] = x; l <= r; x = q[++l])
        		DFOR(i, x, y) q[++r] = y;
		}
		
        string whoCanWin(vector <int> x, vector <int> y, vector <int> r)  
        {  
        	MEM(hd, 0), MEM(sum, 0), MEM(ban, 0), tail = 0;
        	
        	int n = x.size();
        	X[0] = Y[0] = 0, R[0] = 40000;
			REP(i, 1, n) X[i] = x[i - 1], Y[i] = y[i - 1], R[i] = r[i - 1];
			MEM(fa, 0);
			//根据圆的分布还原出树形结构。 
        	REP(i, 1, n) REP(j, 1, n) if (R[i] < R[j] && sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]) < sqr(R[j]) && R[j] < R[fa[i]]) fa[i] = j;
        	REP(i, 1, n) add(fa[i], i);
        	bfs(0);
        	//利用树形dp计算sg函数 
        	PER(now, n, 1){
        		int x = q[now];
        		DFOR(i, x, y) FOR(j, K) if (ban[y][j]) ban[x][j ^ sum[x] ^ sg[y]] = 1;
        		ban[x][sum[x]] = 1;
        		FOR(j, K) if (ban[x][j] == 0){ sum[fa[x]] ^= (sg[x] = j); break; }
			}
			return sum[0] ? "Alice" : "Bob";
        }  
  
};  

