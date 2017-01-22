
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
  
const int N = 300 + 5;
int f[N][N];
vector<int> l, r;
class WolfInZooDivOne  
{  
        public:  
        int count(int n, vector <string> L, vector <string> R)  
        {  
        	int num = 0;
        	l.clear(), r.clear();
        	VEP(i, L) VEP(j, L[i]) 
				if (L[i][j] == ' ') l.PB(num + 1), num = 0;  
				else num = num * 10 + L[i][j] - '0';
			l.PB(num + 1), num = 0;
			VEP(i, R) VEP(j, R[i])
				if (R[i][j] == ' ') r.PB(num + 1), num = 0;
				else num = num * 10 + R[i][j] - '0';
			r.PB(num + 1);
        	int ans = 1;
        	//f[i][j]表示最后两个1的位置为i，j的方案数的前缀和dp状态。 
        	MEM(f, 0), f[0][0] = 1;
        	REP(i, 1, n){
        		f[i][0] = 1;
        		int k = i;
        		VEP(j, l) if (r[j] >= i) cmin(k, l[j]);
        		REP(j, 1, k - 1) f[i][j] = (f[i][j] + f[j][j - 1]) % MOD;
        		REP(j, k, i - 1) f[i][j] = (f[i][j] + f[j][k - 1]) % MOD;
        		REP(j, 1, i - 1) f[i][j] = (f[i][j] + f[i][j - 1]) % MOD;
        		ans = (ans + f[i][i - 1]) % MOD;
			}
			return ans;
        }  
        

};  

