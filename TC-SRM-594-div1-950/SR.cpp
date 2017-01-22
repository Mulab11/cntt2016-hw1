
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
  
int calc(int n, int w, int l, int r, int x){
	return ((n / w - x + 1) * (r - l + 1)) + min(max(n % w - l + 1, 0), r - l + 1);
}
int work(int n, int w, int x, int dep){
	if (n == x && n == 1) return 0 + dep;
	if (n <= w && (x == 1 || x == n)) return 1 + dep;
	if (w == 1 && (x == 1 || x == n)) return 1 + dep;
	if (n % w == 1 && x == n) return 1 + dep;
	if (x == w && n < 2 * w) return 1 + dep;
	if (dep == 2) return 4;
	
	int i = (x - 1) / w + 1, j = (x - 1) % w + 1, ans = inf;
	cmin(ans, work(min(i * w, n), w, x, dep + 1)); //删除下面的矩形 
	REP(k, 1, i - 1) REP(l, 1, w) cmin(ans, work(n - k * l, w, x - k * l, dep + 1)); //删除上面的矩形 
	REP(k, 1, j - 1) REP(l, 1, i) 
		cmin(ans, work(n - calc(n, w, 1, k, l), w, x - (i - l + 1) * k, dep + 1));
	//删除左边的矩形 
	REP(k, 1, w - j) REP(l, 1, i)
		cmin(ans, work(n - calc(n, w, j + 1, j + k, l), w, x - (i - l) * k, dep + 1));
	//删除右边的矩形	
	return ans;
}
class FoxAndAvatar  
{  
        public:  
        int minimalSteps(int n, int width, int x)  
        {  
        	return work(n, width, x, 0);
		}  
      
};  

