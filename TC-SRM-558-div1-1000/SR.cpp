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
#define SFOR(i, x, y) for(int i = sta[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7fffffff;
const int MOD = 1000000007;

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 1000 + 5, M = N * 6 * 2, K = 20 + 5;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
struct Edge{ int nxt, to, flow; } e[M];
int num[N], sta[N], hd[N], tail, s, t, q[N], A[K][K], B[K][K], pos[K][K][2];

//ÍøÂçÁ÷Ä£°å 
void add(int x, int y, int z){
	e[++tail].nxt = hd[x], e[tail].to = y, e[tail].flow = z, hd[x] = tail;
	e[++tail].nxt = hd[y], e[tail].to = x, e[tail].flow = 0, hd[y] = tail;
}
bool bfs(){
	int l, r;
	REP(i, s, t) num[i] = -1, sta[i] = hd[i];
	for (num[q[l = r = 0] = s] = 0; l <= r; l++){
		int x = q[l];
		DFOR(i, x, y)
			if (e[i].flow && !~num[y])
				num[y] = num[x] + 1, q[++r] = y;
	}
	return ~num[t];
}
int dfs(int x, int f){
	if (!f || x == t) return f;
	int g = 0;
	SFOR(i, x, y){
		if (e[i].flow && num[x] + 1 == num[y]){
			int k = dfs(y, min(f - g, e[i].flow));
			e[i].flow -= k, e[i ^ 1].flow += k, g += k;
		}
		sta[x] = i;
		if (f == g) return g;
	}
	return g;
}
int calc(char ch){
	if (ch >= '0' && ch <= '9') return ch - '0';
	if (ch >= 'a' && ch <= 'z') return ch - 'a' + 10;
	if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 36;
}
class SurroundingGame  
{  
        public:  
        int maxScore(vector <string> cost, vector <string> benefit)  
        {  
        	int n = cost.size(), m = cost[0].size();
        	int tot = 0, ans = 0;
        	MEM(hd, 0), tail = 1;
        	s = 0, t = n * m * 2 + 1;
        	//½¨±ß 
        	REP(i, 1, n) REP(j, 1, m) A[i][j] = calc(cost[i - 1][j - 1]);
        	REP(i, 1, n) REP(j, 1, m) ans += (B[i][j] = calc(benefit[i - 1][j - 1]));
        	REP(i, 1, n) REP(j, 1, m) REP(k, 0, 1) pos[i][j][k] = ++tot;
        	REP(i, 1, n) REP(j, 1, m) add(pos[i][j][0], pos[i][j][1], B[i][j]);
        	REP(i, 1, n) REP(j, 1, m) 
				if ((i & 1) ^ (j & 1)) add(s, pos[i][j][0], A[i][j]);
				else add(pos[i][j][1], t, A[i][j]);
			REP(i, 1, n) REP(j, 1, m)	
        		if ((i & 1) ^ (j & 1))
        			FOR(k, 4){
						int ti = i + dx[k], tj = j + dy[k];
						if (ti > 0 && ti <= n && tj > 0 && tj <= m)			
							add(pos[i][j][0], pos[ti][tj][0], inf), add(pos[i][j][1], pos[ti][tj][1], inf);
					}
			while (bfs()) ans -= dfs(s, inf);
			return ans;
        }  
};  
