
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
  
const int N = 100 + 5;
int a[N], vis[N];
class TeamContest  
{  
        public:  
        int worstRank(vector <int> s)  
        {  
        	int n = s.size() - 3, k = min(min(s[0], s[1]), s[2]) + max(max(s[0], s[1]), s[2]);
        	REP(i, 1, n) a[i] = s[i + 2];
        	sort(a + 1, a + n + 1), reverse(a + 1, a + n + 1);//从大到小进行贪心 
        	MEM(vis, 0);
        	int ans = 1;
        	REP(i, 1, n) if (!vis[i]){ 
        		vis[i] = 1;
        		int num = 0;
        		PER(j, n, i + 1) if (!vis[j] && a[j] + a[i] > k){//找到符合条件的最小的两个数组成队伍 
					++num, vis[j] = 1;
					if (num == 2) break;
				}
				if (num == 2) ans++; else break;
			}
			return ans; 
        }  

};  

