
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
int A[N][N], L[N], R[N], visL[N], visR[N], q[N];
class EqualSums  
{  
        public:  
        int count(vector <string> board)  
        {  
        	int n = board.size(), m = board[0].size(), ans1 = 1, ans2 = 1;
        	REP(i, 1, n) REP(j, 1, m) A[i][j] = board[i - 1][j - 1] == '-' ? -1 : board[i - 1][j - 1] - '0';
        	MEM(visL, 0), MEM(visR, 0);
        	
        	//我们通过设未知数，然后bfs的方法得到每个点的常数。 
			REP(now, 1, n) if (!visL[now]){
				visL[now] = 1, L[now] = 0;
				int mn = 0, mx = inf, l, r;
				//mn和mx里面分别维护当前联通块中未知数的合法范围。 
				for (int x = q[l = r = 1] = now; l <= r; x = q[++l]){
					REP(y, 1, m) if (~A[x][y])
						if (visR[y]) if (R[y] + L[x] != A[x][y]) return 0; else;
						else{
							visR[y] = 1;
							cmin(mx, R[y] = A[x][y] - L[x]);
							REP(z, 1, n) if (~A[z][y] && !visL[z]){
								cmax(mn, -(L[z] = A[z][y] - R[y]));
								visL[q[++r] = z] = 1;
							}
						}
				}
				if (mx < mn) return 0; //判断不合法情况，直接返回0； 
				ans1 = (LL)ans1 * (mx - mn + 1) % MOD;
				ans2 = (LL)ans2 * (mx - mn) % MOD;
			}
			return (ans1 - ans2 + MOD) % MOD;
        }  
        

};  

