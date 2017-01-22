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

class PointyWizardHats  
{  
        public:  
        pair<int, double> a[N], b[N];
        int vis[N];
        
        int getNumHats(vector <int> topHeight, vector <int> topRadius, vector <int> bottomHeight, vector <int> bottomRadius)  
        {  
        	int n = topHeight.size(), m = bottomHeight.size(), ans = 0;
        	FOR(i, n) a[i] = MP(topRadius[i], (double)topRadius[i] / topHeight[i]);
        	FOR(i, m) b[i] = MP(bottomRadius[i], (double)bottomRadius[i] / bottomHeight[i]);
        	MEM(vis, 0);
        	sort(a, a + n), sort(b, b + m);
        	FOR(i, m){
        		int k = -1;
        		FOR(j, n) if (!vis[j] && a[j].FT < b[i].FT && a[j].SC < b[i].SC && (!~k || a[j].SC > a[k].SC)) k = j;
        		if (~k) vis[k] = 1, ++ans;
			}
			return ans;
        }  
 
};  
