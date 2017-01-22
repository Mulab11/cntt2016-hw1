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
  
const int N = 1000000 + 5;
int p[N], t, vis[N];
class HolyNumbers  
{  
        public:   
		void Getprime(int n){//预处理素数 
			MEM(vis, 0), t = 0;
			REP(i, 2, n){
				if (!vis[i]) p[++t] = i;
				REP(j, 1, n / i) vis[i * j] = 1;
			}
		}
		LL Getans(LL x, int i){//获得答案 
			if (i > t || p[i] > x) return 1;
			if ((LL)p[i] * p[i] > x) return upper_bound(p + i, p + t + 1, x) - p - i + 1;
			LL tmp = Getans(x, i + 1);
			for (x = x / p[i]; x; x = x / p[i] / p[i]) tmp += Getans(x, i + 1);
			return tmp;
		}
        long long count(long long upTo, int maximalPrime)  
        {  
        	Getprime(maximalPrime);
        	return Getans(upTo, 1);
        }  
    
};  

