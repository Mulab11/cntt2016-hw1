
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
  
const int N = 60 + 5;
int vis[N];
class BitwiseAnd  
{  
        public:  
        vector<long long> lexSmallest(vector<long long> A, int n)  
        {  
        	//每一位最多只能提供两个数
			//两个数之间至少有一个共同位。
			//字典序最小
        	//直接考虑贪心。 
        	vector<long long> bad;
        	int now = 0;
        	MEM(vis, 0);
        	VEP(i, A){
        		int num = 0, mask = 0;
        		++now;
        		FOR(k, 60) if (A[i] >> k & 1){
        			if (vis[k] == -1) return bad; else
        			if (vis[k] == 0){ ++num; vis[k] = now; } else
        			if (vis[k] > 0) mask |= 1ll << (vis[k] - 1), vis[k] = -1;
				}
				if (mask + 1 < (1ll << i)) return bad;
				if (num < n - now) return bad;
			}
			while (now < n){
				LL B = 0;
				REP(i, 1, now) FOR(k, 60) if (vis[k] == i){ vis[k] = -1, B += 1ll << k; break; }
				++now;
				FOR(i, n - now){
					int flag = 0;
					FOR(k, 60) if (vis[k] == 0){ vis[k] = now, flag = 1, B += 1ll << k; break; }
					if (!flag) return bad;
				}
				A.PB(B);
			}
			sort(A.begin(), A.end());
			return A;
        }  

};  

