
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
int hd[N * N], f[N * N], tail, pos[N][N], A, B, DA, DB;
struct Edge{ int nxt, to; } e[N * N * 2];
void add(int x, int y){ if (x && y) e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
void dfs(int x, int fa, int dep){
	if (x == A) DA = dep;
	if (x == B) DB = dep;
	f[x] = 1;
	DFOR(i, x, y) if (y != fa) dfs(y, x, dep + 1), cmax(f[x], f[y] + 1);
}
class GameInDarknessDiv1  
{  
        public:  
        string check(vector <string> field)  
        {  
        	//当存在一个点 P ，满足 dis(A,P)>=dis(B,P)+2，且以 P 为根时有至少 3 个子树的深度大于等于 3 时，Bob 胜，否则 Alice 胜。
        	int tot = 0, n = field.size(), m = field[0].size();
        	MEM(pos, 0), MEM(hd, 0), tail = 0;
        	REP(i, 1, n) REP(j, 1, m) if (field[i - 1][j - 1] != '#'){
        		pos[i][j] = ++tot;
        		if (field[i - 1][j - 1] == 'A') A = tot;
        		if (field[i - 1][j - 1] == 'B') B = tot;
			}
			REP(i, 1, n) REP(j, 1, m){
				add(pos[i][j], pos[i + 1][j]);
				add(pos[i][j], pos[i - 1][j]);
				add(pos[i][j], pos[i][j + 1]);
				add(pos[i][j], pos[i][j - 1]);
			}
			REP(x, 1, tot){
				dfs(x, 0, 0);
				if (DA >= DB + 2){
					int cnt = 0;
					DFOR(tmp, x, y) if (f[y] >= 3) ++cnt;
					if (cnt >= 3) return "Bob wins";
				}
			}
			return "Alice wins";
        }  
    
};  
  
