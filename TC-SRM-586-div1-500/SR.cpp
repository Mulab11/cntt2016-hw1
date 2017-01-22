
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
  
const int N = 26 + 5, M = 10 + 5;
int a[N][M], f[N][N];
class History  
{  
        public:  
        string verifyClaims(vector <string> A, vector <string> B, vector <string> Q)  
        {  
        	//考虑差分约束
			//f[i][j]表示i至多比j大多少，然后求一边floyd最短路，最后求解。 
        	int n = A.size();
        	VEP(i, A){
        		int tmp = 0, num = 0;
				VEP(j, A[i])
					if (A[i][j] == ' ') a[i][tmp++] = num, num = 0; 
					else num = num * 10 + A[i][j] - '0';
				a[i][tmp++] = num;	
			}
			
			MEM(f, 0x3f);
			FOR(i, n) f[i][i] = 0;
			
			//建图 
			string C = "";
			VEP(i, B) C = C + B[i];
			FOR(i, (C.size() + 1) / 6){
				int x = C[i * 6 + 0] - 'A', tx = C[i * 6 + 1] - '0', y = C[i * 6 + 3] - 'A', ty = C[i * 6 + 4] - '0';
				cmin(f[x][y], a[x][tx + 1] - 1 - a[y][ty]), cmin(f[y][x], a[y][ty + 1] - 1 - a[x][tx]);
			}
			
			//floyd 
			FOR(k, n) FOR(i, n) FOR(j, n) cmin(f[i][j], f[i][k] + f[k][j]);
			
			string ans;
			VEP(i, Q){
				int x = Q[i][0] - 'A', tx = Q[i][1] - '0', y = Q[i][3] - 'A', ty = Q[i][4] - '0';
				ans = ans + ((-f[y][x] <= a[x][tx + 1] - 1 - a[y][ty]) && (-f[x][y] <= a[y][ty + 1] - 1 - a[x][tx]) ? 'Y' : 'N');
			}
			return ans;
        }          

};  

