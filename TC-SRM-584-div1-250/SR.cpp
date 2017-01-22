
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
int a[N][N];
class Egalitarianism  
{  
        public:  
        int maxDifference(vector <string> isFriend, int d)  
        {  
        	int n = isFriend.size();
        	//考虑经典的差分约束问题，如果两个之间绝对值小于等于d，那么可以转化为D[A] - D[B] <= d && D[B] - D[A] <= d，求一边最短路即可。 
        	MEM(a, 0x3f);
        	FOR(i, n) a[i][i] = 0;
        	FOR(i, n) FOR(j, n) if (isFriend[i][j] == 'Y') a[i][j] = d;
        	FOR(k, n) FOR(i, n) FOR(j, n) cmin(a[i][j], a[i][k] + a[k][j]);
        	int ans = 0;
        	FOR(i, n) FOR(j, n) cmax(ans, a[i][j]);
        	return ans == inf ? -1 : ans;
        }  

};  

