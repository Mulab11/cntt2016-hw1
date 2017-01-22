
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
#define SFOR(i, x, y) for(int &i = sta[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
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

const int N = 10000 + 5, M = N * 4 * 2, K = 50 + 5;
int hd[N], sta[N], num[N], tail, s, t, L[K][K], R[K][K], q[N];
char a[K][K];
struct Edge{int nxt, to, flow;}e[M];
void add(int x, int y){
	if (x == -1 || y == -1) return;
	e[++tail].nxt = hd[x], e[tail].to = y, e[tail].flow = 1, hd[x] = tail;
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
		if (f == g) return g;
	}
	return g;
}
class TheTilesDivOne  
{  
        public:  
        int find(vector <string> board)  
        {  
        	int n = board.size(), m = board[0].size(), tot = 0;
			tail = 1, MEM(L, -1), MEM(R, -1), MEM(hd, 0);
        	//考虑网络流模型，对于(i+j)偶数点我们设定为2号点，对于i剩余的奇数点我们考虑i是否为奇数，是则为1号点，否则为3号点。
			//那么一条合法的路径包括1->2->3，然后我们不妨进行拆点便可通过网络流求解。 
        	REP(i, 1, n) REP(j, 1, m) a[i][j] = board[i - 1][j - 1];
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == '.') L[i][j] = ++tot, R[i][j] = ++tot, add(L[i][j], R[i][j]);
        	s = 0, t = tot + 1;
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == '.')
				if ((i + j) & 1)
        			if (i & 1) add(s, L[i][j]), add(R[i][j], L[i + 1][j]), add(R[i][j], L[i - 1][j]), add(R[i][j], L[i][j + 1]), add(R[i][j], L[i][j - 1]);
        			else add(R[i][j], t), add(R[i + 1][j], L[i][j]), add(R[i - 1][j], L[i][j]), add(R[i][j + 1], L[i][j]), add(R[i][j - 1], L[i][j]);
        	int ans = 0;
        	while (bfs()) ans += dfs(s, inf);
        	return ans;
        }
        
};  

