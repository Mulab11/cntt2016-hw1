
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
  
const int K = 50 + 5, N = K * K;
int pos[K][K];
char a[K][K];
int num[N], sta[N], hd[N], tail, s, t, q[N];
struct Edge{ int nxt, to, flow; } e[N * 4 * 2];

//网络流模板 
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
class FoxAndGo3  
{  
        public:  
        int maxEmptyCells(vector <string> board)  
        {  
        	//问题转化为白块和空格的二分图的最大独立集问题，直接跑网络流或者二分图匹配即可。 
        	int n = board.size(), m = board.size(), tot = 0;
        	MEM(hd, 0), MEM(a, 'x'), MEM(pos, 0);
        	REP(i, 1, n) REP(j, 1, m) a[i][j] = board[i - 1][j - 1];
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] != 'x') pos[i][j] = ++tot;
        	s = 0, t = tot + 1, tail = 1;
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == 'o'){
        		add(pos[i][j], pos[i + 1][j], 1);
        		add(pos[i][j], pos[i][j + 1], 1);
        		add(pos[i][j], pos[i - 1][j], 1);
        		add(pos[i][j], pos[i][j - 1], 1);
        		add(s, pos[i][j], 1);
			} else 
				if (a[i][j] == '.') add(pos[i][j], t, 1);
				
			int ans = tot;
			while (bfs()) ans -= dfs(s, inf);
			return ans;
        }  
        
};  

