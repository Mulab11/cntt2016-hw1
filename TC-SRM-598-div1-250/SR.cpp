
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
int vis[N];
class BinPacking  
{  
        public:  
        int minBins(vector <int> a)  
        {  
        	//重量 > 100的肯定尽量两两配对
			// == 100的剩余的，可以33配对。 
        	sort(a.begin(), a.end());
			reverse(a.begin(), a.end());
			int n = a.size(), ans = 0, top3 = 0;
			MEM(vis, 0);
			FOR(i, n) if (!vis[i]) if (a[i] > 100){
				REP(j, i + 1, n) if (a[i] + a[j] <= 300 & !vis[j]) {vis[j] = 1; break;}
				++ans;
			} else ++top3;
			return ans + (top3 + 2) / 3;
        }  

};  

