
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
  
const int N = 300000 + 6;
PI a[N];
vector<PI> b;
int f[N], g[N];
LL Sum[N];
inline PI operator - (const PI &a, const PI &b){ return MP(a.FT - b.FT, a.SC - b.SC); }
inline LL operator * (const PI &a, const PI &b){ return (LL)a.FT * b.SC - (LL)a.SC * b.FT; }

class EnclosingTriangle  
{  
        public:  
        
        bool ok(const PI &A, const PI &B){
        	VEP(i, b) if ((B - A) * (b[i] - A) < 0) return 0;
        	return 1;
		}
        long long getNumber(int m, vector <int> x, vector <int> y)  
        {  
        	int n = m * 4;
        	b.clear();
        	FOR(i, m) a[i] = MP(i, 0);
        	FOR(i, m) a[i + m] = MP(m, i);
        	FOR(i, m) a[i + 2 * m] = MP(m - i, m);
        	FOR(i, m) a[i + 3 * m] = MP(0, m - i);
        	VEP(i, x) b.PB(MP(x[i], y[i]));
        	
        	//预处理f和g数组，f里面存最大的似的i->f[i]这条向量合法，g里面存最小的g[i]->i这条向量合法。
			int j = 1;
			FOR(i, n){ while (j < n - 1 && ok(a[i], a[j + 1])) ++j; f[i] = j; }
			j = 1;
			FOR(i, n){ while (j < n && !ok(a[j], a[i])) ++j; g[i] = j; }
			
			//预处理前缀和 
			REP(i, 1, n) Sum[i] = Sum[i - 1] + f[i - 1];
			LL ans = 0;
			FOR(i, n) if (g[i] < n) {
				//找到最小的f[j]使得f[j]>=g[i]。 
				int j = lower_bound(f, f + n, g[i]) - f;
				cmin(j, f[i]), cmax(j, i + 1);
				ans += Sum[f[i]] - Sum[j] - LL(f[i] - j) * (g[i] - 1);
				ans += max(f[f[i]] - max(g[i], f[i] + 1) + 1, 0);
			}
			return ans;
        }  

};  

