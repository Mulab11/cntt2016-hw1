
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
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int vis[N][N], change[N], f[N][N][N], n, m, L[N], R[N], cnt[N][N];
vector<string> G;
PI A, B;
class Tunnels  
{  
        public:  
        void dfs(int i, int j){
        	if (i >= n || j < 0 || j >= m || G[i][j] == '.' || vis[i][j] == 1) return;
        	vis[i][j] = 1;
        	if (cnt[i][j] == 1) A = B, B = MP(i, j);
        	else if (cnt[i][j] == 0) A = B = MP(i, j);
        	dfs(i + 1, j), dfs(i, j + 1), dfs(i, j - 1);
		}
        int minimumTunnels(vector <string> frame)  
        {  
        	MEM(change, 0), MEM(vis, 0), MEM(L, 0), MEM(R, 0), MEM(f, -1), MEM(cnt, 0);
        	int tot = 0;
        	G = frame;
        	n = G.size(), m = G[0].size();
        	FOR(i, n) FOR(j, m) if (G[i][j] == 'X'){
        		cnt[i][j] = 0;
        		FOR(k, 4){
        			int di = i + dx[k], dj = j + dy[k];
        			if (di >= 0 && di < n && dj >= 0 && dj < m && G[di][dj] == 'X') ++cnt[i][j];
				}
			}
        	FOR(i, n) FOR(j, m) if (!vis[i][j] && G[i][j] == 'X'){
        		dfs(i, j); 
				++tot; 
				if (A > B) swap(A, B);
        		if (A.FT == B.FT && A.SC == 0 && B.SC == m - 1) change[i] = 1; //当前行一条龙贯穿的方案 
        		else
        			if (i == 0){//头顶着顶层 
        				if (B.FT == 0 && B.SC > 0 && B.SC < m - 1) swap(A, B);
						if (B.SC == 0) L[B.FT]++;
						if (B.SC == m - 1) R[B.FT]++;
					} else {
						if (B.FT == A.FT && (B.SC == 0 || B.SC == m - 1)) swap(A, B);
						if (A.SC == 0){ //在左边的括号 
							L[A.FT]--;
							if (B.SC == 0 && B.FT > A.FT + 1) L[B.FT]++;
							if (B.SC == m - 1) R[B.FT]++;
						} else
						if (A.SC == m - 1){
							R[A.FT]--;
							if (B.SC == m - 1 && B.FT > A.FT + 1) R[B.FT]++;
							if (B.SC == 0) L[B.FT]++;
						}
					}
			}
			if (m == 1) return int(tot > 0); //特判，如果列为1那么显然可以一条龙贯穿下去 
			f[0][0][0] = 0;
			FOR(i, n) REP(j, 0, i) REP(k, 0, i) if (f[i][j][k] > -1)
				if (change[i])
					cmax(f[i + 1][j + 1][max(k - 1, 0)], f[i][j][k] + bool(k)), //两边均贯通
					cmax(f[i + 1][max(j - 1, 0)][k + 1], f[i][j][k] + bool(j));
				else cmax(f[i + 1][max(j + L[i], 0)][max(k + R[i], 0)], f[i][j][k] + (L[i] == -1 && j) + (R[i] == -1 && k));//直接括号匹配 
			int ans = -1;
			REP(i, 0, n) REP(j, 0, n) cmax(ans, f[n][i][j]);
			return tot - ans;
        }  

};  

