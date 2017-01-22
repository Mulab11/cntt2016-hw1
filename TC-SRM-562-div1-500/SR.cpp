
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

const int N = 220 + 5;
int wx[N], wy[N], bx[N], by[N];
PI a[N], b[N];
bitset<N> A[N][N], B[N][N], C[N][N];

inline PI operator - (const PI &a, const PI &b){ return MP(a.FT - b.FT, a.SC - b.SC); }
inline LL operator * (const PI &a, const PI &b){ return (LL)a.FT * b.SC - (LL)a.SC * b.FT; }
void get(vector<string> a, int b[], int &n){
	b[n = 1] = 0;
	VEP(i, a) VEP(j, a[i])
		if (a[i][j] == ' ') { b[++n] = 0; }
		else b[n] = b[n] * 10 + a[i][j] - '0';
}  
class CheckerFreeness  
{  
        public:  
        string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY)  
        {  
        	int n, m;
        	get(whiteX, wx, n), get(whiteY, wy, n), get(blackX, bx, m), get(blackY, by, m);
        	REP(i, 1, n) a[i] = MP(wx[i], wy[i]);
        	REP(i, 1, m) b[i] = MP(bx[i], by[i]);
        	//一个压位的布尔数组i,j,k表示第对于i->j这条射线来说，是1表示在这条射线右边，反之，0表示在这条射线左边。 
        	REP(i, 1, n) REP(j, 1, n) if (i != j){
        		A[i][j].reset();
        		REP(k, 1, m) if ((b[k] - a[i]) * (a[j] - a[i]) > 0) A[i][j][k] = 1;
        	}
        	REP(i, 1, m) REP(j, 1, n){
        		B[i][j].reset();
        		REP(k, 1, m) if ((b[k] - b[i]) * (a[j] - b[i]) > 0) B[i][j][k] = 1;
			}
			REP(i, 1, n) REP(j, 1, m){
        		C[i][j].reset();
        		REP(k, 1, m) if ((b[k] - a[i]) * (b[j] - a[i]) > 0) C[i][j][k] = 1;
			}
			REP(i, 1, n) REP(j, 1, n) if (i != j)
				REP(k, 1, m) if (A[i][j][k])
					if ((A[j][i] & B[k][i] & C[j][k]).count()) return "NO";
			return "YES";		
        }  
    
};  

