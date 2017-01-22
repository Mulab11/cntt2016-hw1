
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
const int inf = 0x3f3f3f3f;
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
int L[N], R[N], T[N], a[N][N], f[(1 << 18) + 5][18 + 5];
class TravellingPurchasingMan  
{  
        public:  
        int maxStores(int n, vector <string> F, vector <string> roads)  
        {  
        	int m = F.size();
        	FOR(i, m){
				istringstream ss(F[i]);
		        ss >> L[i] >> R[i] >> T[i];
		    }
		    MEM(a, 0x3f), MEM(f, 0x3f);
		    FOR(i, n) a[i][i] = 0;
		    VEP(i, roads){
		    	int x, y, z;
		    	istringstream ss(roads[i]);
		    	ss >> x >> y >> z;
		    	a[x][y] = a[y][x] = z;
			}
			FOR(k, n) FOR(i, n) FOR(j, n) cmin(a[i][j], a[i][k] + a[k][j]);

			//考虑状压dp ,f[i][j]表示购买了关于二进制压位bit i的商品，然后最后到达商品店j的最早时间。 
			FOR(i, m) f[0][i] = a[n - 1][i];
			FOR(i, (1 << m) - 1){
				FOR(j, m) FOR(k, m) cmin(f[i][k], f[i][j] + a[j][k]);
				FOR(j, m) if ((i >> j & 1 ^ 1) && f[i][j] <= R[j])
					cmin(f[i | 1 << j][j], max(f[i][j], L[j]) + T[j]);
			}
			int ans = 0;
			FOR(i, 1 << m) FOR(j, m) if (f[i][j] < inf) cmax(ans, __builtin_popcount(i));
			return ans;
        }  
        

};  

