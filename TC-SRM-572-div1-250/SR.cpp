
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
  
const int N = 26 + 6;
int ch[N];

class NewArenaPassword  
{  
        public:  
        int minChange(string s, int K)  
        {  
        	int n = s.size(), ans = 0;
        	if (K <= n / 2) FOR(i, K) ans += (s[i] != s[n - K + i]);
        	else{
        		int m = n - K; //如果K > n / 2的话那么s最终形态应该是开头以n-K为循环的循环串 
        		FOR(i, m){
        			FOR(j, 26) ch[j] = 0;
					for(int j = i; j < n; j += m) ch[s[j] - 'a']++, ans++;
					int mx = 0;
					FOR(j, 26) cmax(mx, ch[j]);
					ans -= mx;
				}
			}
			return ans;
        }  
        
};  
  

