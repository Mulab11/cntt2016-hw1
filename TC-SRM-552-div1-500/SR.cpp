
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

const int N = 30 + 4;
PI S[N][N];
int LR[2][N][N * N * 2], UD[2][N][N * N * 2];       
inline PI operator + (const PI &A, const PI &B){ return MP(A.FT + B.FT, A.SC + B.SC); }
inline PI operator - (const PI &A, const PI &B){ return MP(A.FT - B.FT, A.SC - B.SC); }
class FoxAndFlowerShopDivOne  
{  
        public:  

        int calc(int x, int y){ return (~x && ~y) ? x + y : -1; }
        int theMaxFlowers(vector <string> flowers, int maxDiff)  
        {  
        	int n = flowers.size(), m = flowers[0].size(), ans = -1;
        	int K = 900; // K用来消除数组负数域 
        	MEM(S, 0), MEM(UD, -1), MEM(LR, -1);
        	REP(i, 1, n) REP(j, 1, m){
				S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1];
				S[i][j].FT += flowers[i - 1][j - 1] != '.';
				S[i][j].SC += flowers[i - 1][j - 1] == 'P' ? 1 : (flowers[i - 1][j - 1] == 'L' ? -1 : 0);
			}
			//预处理边界最大值 
			FOR(i, n) FOR(j, m) REP(k, i + 1, n) REP(l, j + 1, m){
				PI tmp = S[k][l] + S[i][j] - S[i][l] - S[k][j];
				cmax(UD[0][k][tmp.SC + K], tmp.FT);
				cmax(UD[1][i][tmp.SC + K], tmp.FT);
				cmax(LR[0][l][tmp.SC + K], tmp.FT);
				cmax(LR[1][j][tmp.SC + K], tmp.FT);
			} 
			//迭代更新，获得前缀和最大值 
			REP(j, 0, K * 2){
				REP(i, 1, n - 1) cmax(UD[0][i][j], UD[0][i - 1][j]);
				PER(i, n - 1, 1) cmax(UD[1][i][j], UD[1][i + 1][j]);
				REP(i, 1, m - 1) cmax(LR[0][i][j], LR[0][i - 1][j]);
				REP(i, m - 1, 1) cmax(LR[1][i][j], LR[1][i + 1][j]);
			}
			//合并两块部分更新最优解 
			REP(i, 0, K * 2) REP(j, max(K * 2 - i - maxDiff, 0), min(K * 2 - i + maxDiff, K * 2)){
				REP(k, 1, n - 1) cmax(ans, calc(UD[0][k][i], UD[1][k][j])); 
				REP(k, 1, m - 1) cmax(ans, calc(LR[0][k][i], LR[1][k][j]));
			}
			return ans;
        }  
    
};  

