
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
  
const int K = 100 + 5, N = 10000 + 5, M = N * 8;
int hd[N], sta[N], num[N], tail, s, t, q[N], pos[K][K], in[N], out[N];
char a[K][K];
struct Edge{int nxt, to, flow;}e[M];
void add(int x, int y, int z){
	if (x == -1 || y == -1) return;
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
		if (f == g) return g;
	}
	return g;
}
class BoardPainting  
{  
        public:  
        int minimalSteps(vector <string> target)  
        {  
        	int n = target.size(), m = target[0].size(), tot = 1;
        	MEM(a, '.');
        	REP(i, 1, n) REP(j, 1, m) a[i][j] = target[i - 1][j - 1];
        	MEM(pos, -1), MEM(in, 0), MEM(out, 0);
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == '#') pos[i][j] = ++tot;
        	REP(i, 0, n + 1) REP(j, 0, m + 1) if (a[i][j] == '.'){
        		if (~pos[i + 1][j]) in[pos[i + 1][j]]++; 
        		if (~pos[i - 1][j]) in[pos[i - 1][j]]++;
        		if (~pos[i][j + 1]) out[pos[i][j + 1]]++;
        		if (~pos[i][j - 1]) out[pos[i][j - 1]]++;
        	}
        	s = 0, t = tot + 1, tail = 1, MEM(hd, 0);
        	REP(i, 1, tot) add(s, i, in[i]), add(i, t, out[i]);
        	REP(i, 1, n) REP(j, 1, m) if (a[i][j] == '#'){
        		add(pos[i][j], pos[i + 1][j], 1);
        		add(pos[i][j], pos[i - 1][j], 1);
        		add(pos[i][j], pos[i][j + 1], 1);
        		add(pos[i][j], pos[i][j - 1], 1);
			}
			int ans = 0;
        	while (bfs()) ans += dfs(s, inf);
        	return ans / 2;
        }  
       
};  

