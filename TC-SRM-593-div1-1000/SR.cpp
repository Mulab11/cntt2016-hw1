
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
  

const int N = 2000000 + 5;
int s[N], l[N], tail, hd[N], n, f[N];
struct Edge{ int nxt, to; } e[N];
char st[N];

void addedge(int x, int y){ e[++tail] = (Edge){hd[x], y}, hd[x] = tail; }
void add(int x, int d){
	++x;
	while (x <= n + 1) s[x] = ((LL)s[x] + d + MOD) % MOD, x += x & (-x);
}
int query(int x){
	int ans = 0;
	++x;
	if (x < 1) return 0;
	while (x) ans = (ans + s[x]) % MOD, x -= x & (-x);
	return ans;
}
class WolfDelaymasterHard  
{  
        public:  
        int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)  
        {  
        	::n = n;
        	MEM(s, 0), MEM(hd, 0), tail = 0;
        	
        	REP(i, 1, n) st[i] = '?';
        	LL x = w0;
			for(int i = 0;i < wlen; i++){
				st[x + 1] = 'w';				// Rewrite the x-th (0-based) character of s
				x = (x * wmul + wadd) % n;
			}
			x = o0;
			for(int i = 0; i < olen; i++){
				st[x + 1] = 'o';				// Rewrite the x-th (0-based) character of s
				x = (x * omul + oadd) % n;
			}
			
			//我们维护l[i]和r[i],l[i]表示第一个小于等于i的o的位置，r[i]表示第一个大于i的w的位置
			//那么我们发现j(j<i)可以转移到i的条件是， r[j]>(i+j)/2,l[i]<=(i+j)/2。
			//就转化为 2l[i]-i<=j,2r[j]-j>i。
			//然后我们可以通过用树状数组维护前缀和，对于每一个f[i],我们在 2r[j]-j 的位置打上标记，表示退出。 
			l[0] = 0;
			REP(i, 1, n) l[i] = st[i] == 'w' ? i : l[i - 1];
			int r = n + 1;
			PER(i, n - 1, 0){
				if (st[i + 1] == 'o') r = i + 1;;
				addedge(min(r * 2 - i, n + 1), i);
			}
			
			add(0, 1), f[0] = 1;
			REP(i, 1, n){
				DFOR(now, i, x) add(x, -f[x]);
				if (i & 1 ^ 1) f[i] = ((LL)query(i) - query(2 * l[i] - i - 1) + MOD) % MOD;
				add(i, f[i]);
			}
			return f[n];
		}  
   
};  

