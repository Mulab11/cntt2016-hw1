
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
  
const int N = 300 + 5;
int a[N], f[N][2];
class FlippingBitsDiv1  
{  
        public:  
        int getmin(vector <string> S, int m)  
        {  
        	string A;
        	VEP(i, S) A += S[i];
        	int n = A.size(), t = n / m, ans = inf;
        	//设t = n / m， 那么t和m之间必然存在一个小于等于17的数
			//然后我们考虑t<=17的情况，我们可以枚举每一位k*M的前缀每一个是否翻转，然后进行统计 
			//我们再考虑m<=17的情况，我们可以枚举循环节，然后进行dp 
        	if (t < m)
        		FOR(now, 1 << t){
        			int tmp = 0;
        			FOR(i, n) a[i] = A[i] - '0';
        			ROF(i, t){
        				tmp ^= now >> i & 1;
						FOR(j, m) a[i * m + j] ^= tmp;
					}
					int tmpans = 0;
					FOR(i, m){
						int c[2] = {0, 0};
						for (int j = i; j < n; j += m) ++c[a[j]];
						tmpans += min(c[0], c[1]);
					}
					cmin(ans, tmpans + __builtin_popcount(now));
				}
			else 
				FOR(now, 1 << m){
					MEM(f, 0x3f);
					f[0][0] = 0, f[0][1] = 1;
					MEM(a, 0);
					FOR(i, t) FOR(j, m) a[i] |= (A[i * m + j] - '0') << j;
					FOR(i, t) FOR(j, 2) if (f[i][j] < inf)
						cmin(f[i + 1][0], f[i][j] + __builtin_popcount(a[i] ^ now)),
						cmin(f[i + 1][1], f[i][j] + __builtin_popcount(a[i] ^ now ^ ((1 << m) - 1)) + (j ^ 1) * 2);
					int tmpans = min(f[t][0], f[t][1]);
					FOR(i, n % m) if ((now >> i & 1) != (A[t * m + i] - '0')) ++tmpans;
					cmin(ans, tmpans);
				}
			return ans;	
        }  
  
};  

