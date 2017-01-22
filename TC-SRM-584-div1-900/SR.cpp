
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
int in[N], pre[N], vis[N], col[N], A[N];
struct Edge{ int x, y, dis; } e[N * N];
class FoxTheLinguist  
{  
        public:  
        int minimalHours(int n, vector <string> All)  
        {  
        	//建立最小树形图使用朱刘算法。 
        	string a;
			VEP(i, All) a += All[i];
			int m = (a.size() + 1) / 12, tot = 0;
			
			MEM(A, 0x3f);
			FOR(i, m){
				int x = (a[i * 12 + 0] - 'A') * 10 + (a[i * 12 + 1] - '0') + 1,
					y = (a[i * 12 + 4] - 'A') * 10 + (a[i * 12 + 5] - '0') + 1,
					z = (a[i * 12 + 7] - '0') * 1000 + (a[i * 12 + 8] - '0') * 100 + (a[i * 12 + 9] - '0') * 10 + (a[i * 12 + 10] - '0');
				e[++tot] = (Edge){x, y, z};	
			}
			FOR(i, n) PER(j, 9, 1) e[++tot] = (Edge){i * 10 + j + 1, i * 10 + j, 0};
			FOR(i, n) e[++tot] = (Edge){0, i * 10 + 1, 0};
			n = n * 10;
						
			int ans = 0;
			int c = 0;
			while (1){
				REP(i, 1, n) in[i] = inf, pre[i] = 0;
				REP(i, 1, tot){
					int x = e[i].x, y = e[i].y, z = e[i].dis;
					if (x != y && z < in[y]) in[y] = z, pre[y] = x;
				}
				REP(i, 1, n) if (in[i] == inf) return -1;
				REP(i, 1, n) ans += in[i];
				
				MEM(vis, 0), MEM(col, 0);
				int cnt = 0;
				REP(i, 1, n){
					int x = i;
					while (x && !vis[x]) vis[x] = i, x = pre[x];
					if (x && vis[pre[x]] == i){
						++cnt; while (!col[x]) col[x] = cnt, x = pre[x];
					}
				}
				if (!cnt) return ans;
				REP(i, 1, n) if (!col[i]) col[i] = ++cnt;
				REP(i, 1, tot){
					int x = e[i].x, y = e[i].y;
					e[i].dis -= in[y], e[i].x = col[x], e[i].y = col[y];
				}
				n = cnt;
			}
        }  

};  

