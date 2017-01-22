
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
#define DFOR(i, x) for(int i = hd[x]; i; i = e[i].nxt)
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

const int N = 50 + 5, M = 50 * 50 + 5;
int pos[N][N], fa[M], tail, hd[M];
struct Edge{ int nxt, x, y; } e[M * 2];
void add(int x, int a, int b){ e[++tail] = (Edge){hd[x], a, b}, hd[x] = tail; }
int getfa(int x){ return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
class ArcadeManao  
{  
        public:  

		int shortestLadder(vector<string> level, int coinRow, int coinColumn)
		{
			MEM(hd, 0), tail = 0;
			int n = level.size(), m = level[0].size(), tot = 0;
			FOR(i, n) FOR(j, m) if (level[i][j] == 'X') pos[i][j] = ++tot; 
			int coin = pos[coinRow - 1][coinColumn - 1], start = tot;
			FOR(i, tot) fa[i] = i;
			//并查集维护连通性 
			FOR(i, n) FOR(j, m - 1) if(level[i][j] == 'X' && level[i][j + 1] == 'X')
				fa[getfa(pos[i][j])] = getfa(pos[i][j + 1]);
			FOR(j, m){
				int last = n - 1;
				ROF(i, n - 1) if(level[i][j] == 'X')
					add(last - i, pos[i][j], pos[last][j]), last = i;
			}
			FOR(now, n){//枚举梯子长度 
				DFOR(i, now) fa[getfa(e[i].x)] = getfa(e[i].y);
				if(getfa(start) == getfa(coin)) return now;
			}
		}
        
  
};  
  

