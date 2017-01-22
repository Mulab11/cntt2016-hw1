
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
  
  
class ICPCBalloons  
{  
        public:  
        int minRepaintings(vector <int> bc, string bs, vector <int> ma)  
        {  
        	vector<int> s[2];
        	
        	int n = bc.size(), m = ma.size();
        	FOR(i, n) s[bs[i] == 'L'].PB(bc[i]);
        	FOR(i, 2) sort(s[i].begin(), s[i].end()), reverse(s[i].begin(), s[i].end());
        	int ans = inf;
        	FOR(now, 1 << m){//枚举每道题使用M号气球还是L号气球 
        		vector<int> t[2];
        		
				FOR(i, m) t[now >> i & 1].PB(ma[i]);
				FOR(i, 2) sort(t[i].begin(), t[i].end()), reverse(t[i].begin(), t[i].end());
				
				//然后从大到小排序，贪心计算。 
				int tmpans = 0;
				FOR(tp, 2){
					int tot1 = 0, tot2 = 0;
					VEP(i, s[tp]) tot1 += s[tp][i];
					VEP(i, t[tp]) tot2 += t[tp][i];
					if (tot1 < tot2){ tmpans = inf; break; }
					VEP(i, t[tp]) tmpans += t[tp][i] - min(i < s[tp].size() ? s[tp][i] : 0, t[tp][i]);
				}
				cmin(ans, tmpans);
			}
			return ans == inf ? -1 : ans;
        }  
     
};  

