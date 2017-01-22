
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
  
const int N = 10000 + 5;
int a[N];
class TheTree  
{  
        public:  
        int maximumDiameter(vector <int> cnt)  
        {  
        	//枚举直径的两个点的深度，和lca的深度判断是否合法。 
        	int n = cnt.size(), ans = 0;
        	a[0] = 1;
        	REP(i, 1, n) a[i] = cnt[i - 1];
        	REP(i, 0, n) REP(j, i, n) REP(k, j, n){
        		int flag = 1;
        		REP(l, i + 1, j) if (a[l] == 1){ flag = 0; break; }
        		if (flag) cmax(ans, j + k - i - i);
			}
        	return ans;
        }  
    
};  

