
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
const int MOD = 1000000009;

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

const int N = 40 + 5;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
struct Data{ int n[4]; } s[N][N];
int a[N][N], f[N][N], cnt[N * N], pw[N * N];

inline bool operator < (const Data &a, const Data &b){
	FOR(i, 4){
		if (a.n[i] < b.n[i]) return 1;
		if (a.n[i] > b.n[i]) return 0;
	}
	return 0;
}
inline bool operator ==  (const Data &a, const Data &b){
	return !((b < a) || (a < b));
}
class CoinsGame  
{  
        public:  
        int ways(vector <string> board)  
        {  
        	int n = board.size(), m = board[0].size();
        	MEM(f, 0), MEM(a, 0), MEM(cnt, 0);
        	REP(i, 1, n) REP(j, 1, m) a[i][j] = board[i - 1][j - 1] == '#';
        	REP(i, 1, n) REP(j, 1, m) if (!a[i][j]) f[i][j] = 1;
        	FOR(now, n * m){
        		vector<Data> tmp;
        		REP(i, 1, n) REP(j, 1, m) if (!a[i][j]){
					FOR(k, 4) s[i][j].n[k] = a[i + dx[k]][j + dy[k]] ? f[i][j] : f[i + dx[k]][j + dy[k]];
					tmp.PB(s[i][j]);
				}
				sort(tmp.begin(), tmp.end());
				tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
				REP(i, 1, n) REP(j, 1, m) if (!a[i][j]) f[i][j] = lower_bound(tmp.begin(), tmp.end(), s[i][j]) - tmp.begin() + 1;
			}
			pw[0] = 1;
			REP(i, 1, n * m) pw[i] = pw[i - 1] * 2 % MOD;
			int ans = 0, tot = 0;
			REP(i, 1, n) REP(j, 1, m) cnt[f[i][j]]++;
			REP(i, 1, n * m) if (cnt[i]) ans = (ans + MOD - pw[cnt[i]] + 1) % MOD, tot += cnt[i];
			ans = (ans + pw[tot] - 1) % MOD;
			return ans;
        }  
  
};  

