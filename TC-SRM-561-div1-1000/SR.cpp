// BEGIN CUT HERE  
/* 
 
*/  
// END CUT HERE  
#line 7 "Orienteering.cpp"  

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
  
const int N = 2500 + 5;
int tail, hd[N], q[N], fa[N], sz[N], d[N], dis[N][N], pos[50 + 5][50 + 5];
vector<int> s;
struct Edge{ int nxt, to; } e[N * 2];
void add(int x, int y){ 
	if (!x || !y) return;
	e[++tail] = (Edge){hd[x], y}, hd[x] = tail;
	e[++tail] = (Edge){hd[y], x}, hd[y] = tail;
}
void bfs(int x){
	int l, r;
	for(fa[q[l = r = 1] = x] = 0; l <= r; x = q[++l])
		DFOR(i, x, y) if (y != fa[x]) fa[q[++r] = y] = x;
}
double f(int a, int b, int k){
	if (a >= k && b >= a){
		double ans = 1;
		REP(i, 1, b - a) ans = ans * (a - k + i) / (a + i);
		return ans;
	}
	return 0;
}
class Orienteering  
{  
        public:  
        double expectedLength(vector <string> field, int K)  
        {  
        	MEM(hd, 0), tail = 0, s.clear(), MEM(fa, 0);
        	MEM(sz, 0), MEM(d, 0), MEM(dis, 0);
        	int n = field.size(), m = field[0].size(), tot = 0, k;
        	
			FOR(i, n) FOR(j, m){
				sz[pos[i][j] = field[i][j] == '#' ? 0 : ++tot] = field[i][j] == '*';
				if (sz[pos[i][j]]) s.PB(pos[i][j]);
			}
			FOR(i, n) FOR(j, m - 1) add(pos[i][j], pos[i][j + 1]);
			FOR(i, n - 1) FOR(j, m) add(pos[i][j], pos[i + 1][j]);
			
			n = tot, k = s.size();
			bfs(1);
			PER(i, n, 1) sz[fa[q[i]]] += sz[q[i]];
			
			//答案可以分为两部分，即期望最小子树上所有边长度之和*2-期望最小子树的直径 
			
			//计算第一部分答案 
			double ans = 0;
			REP(i, 2, n) ans += 1 - f(sz[i], k, K) - f(k - sz[i], k, K);
			ans *= 2;
			//计算第二部分答案
			REP(i, 1, n) d[q[i]] = d[fa[q[i]]] + 1;
			REP(x, 1, n) REP(y, 1, n){
				int i = q[x], j = q[y];
				if (i == j) dis[i][j] = 0; else
				if (d[i] < d[j]) dis[i][j] = dis[i][fa[j]] + 1; else
				if (d[i] > d[j]) dis[i][j] = dis[fa[i]][j] + 1; else
				dis[i][j] = dis[fa[i]][fa[j]] + 2;
			}
			REP(i, 0, k - 1) REP(j, i + 1, k - 1){
				int cnt = 0;
				//注意我们考虑存在多个直径相同的部分，我们选择在枚举编号最小的两个点的时候计算入总答案 
				REP(o, 0, i) if (o != i && o != j && dis[s[i]][s[j]] > dis[s[i]][s[o]] && dis[s[i]][s[j]] > dis[s[j]][s[o]]) ++cnt;
				REP(o, i, j) if (o != i && o != j && dis[s[i]][s[j]] > dis[s[i]][s[o]] && dis[s[i]][s[j]] >= dis[s[j]][s[o]]) ++cnt;
				REP(o, j + 1, k - 1) if (o != i && o != j && dis[s[i]][s[j]] >= dis[s[i]][s[o]] && dis[s[i]][s[j]] >= dis[s[j]][s[o]]) ++cnt;
				ans -= dis[s[i]][s[j]] * f(cnt, k - 2, K - 2) * (K - 1) * K / (k - 1) / k;
			}
			return ans;
        }  
};  

