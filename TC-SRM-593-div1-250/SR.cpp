
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
  
const int N = 50 + 5, K = N * N;
int pos[N][N], col[K], hd[K], tail = 0;
struct Edge{int nxt, to;} e[K * 6];
class HexagonalBoard  
{  
        public:  
        void add(int x, int y){
        	if (!x || !y) return;
        	e[++tail] = (Edge){hd[x], y}, hd[x] = tail;
        	e[++tail] = (Edge){hd[y], x}, hd[y] = tail;
		}
		int dfs(int x, int c){
			if (!~col[x]) col[x] = c;
			else return col[x] != c;
			DFOR(i, x, y) if (dfs(y, c ^ 1)) return 1;
			return 0;
		}
        int minColors(vector <string> board)  
        {  
        	//首先至多只要三种颜色
			//那么我们剩下的我们只要判断2种颜色是否合法，1种颜色是否合法即可。
			//不难发现只要建图后判断是否为2分图即可。 
        	int n = board.size(), m = board[0].size(), tot = 0;
        	MEM(pos, 0), MEM(hd, 0), tail = 0;
        	REP(i, 1, n) REP(j, 1, m) if (board[i - 1][j - 1] == 'X') pos[i][j] = ++tot;
        	REP(i, 1, n) REP(j, 1, m) add(pos[i][j], pos[i - 1][j]), add(pos[i][j], pos[i - 1][j + 1]), add(pos[i][j], pos[i][j - 1]);
        	
        	MEM(col, -1);
        	int cnt = 0;
        	REP(i, 1, tot) if (!~col[i]){
				if (dfs(i, 0)) return 3;
				++cnt;
			}
			if (tot == 0) return 0;
			if (cnt == tot) return 1; 
			return 2;
        }  
 
};  

