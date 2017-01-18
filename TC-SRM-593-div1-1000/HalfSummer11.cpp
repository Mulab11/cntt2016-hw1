#line 2 "WolfDelaymasterHard.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 2000010
#define mo 1000000007
typedef long long ll;
using namespace std;
int g[maxn], Sum[maxn], lw[maxn], lo[maxn], rw[maxn], ro[maxn];
char s[maxn];
void add(int &a, int b) {
	a += b; a %= mo;
}
class WolfDelaymasterHard {
	public:
		int countWords(int n, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
			for (int i = 1; i <= n; ++i) s[i] = '?'; 
			int x = w0;
			for (int i = 0; i < wlen; ++i) {
				s[x + 1] = 'w';
				x = (1ll * x * wmul % n + wadd) % n;
			}
			x = o0;
			for (int i = 0; i < olen; ++i) {
				s[x + 1] = 'o';
				x = (1ll * x * omul % n + oadd) % n;
			}
			lw[0] = lo[0] = -1;
			for (int i = 1; i <= n; ++i) {
				lw[i] = (s[i] == 'w') ? i : lw[i - 1];
				lo[i] = (s[i] == 'o') ? i : lo[i - 1];
			}
			ro[n + 1] = rw[n + 1] = -1;
			for (int i = n; i >= 0; --i) {
				rw[i] = (s[i] == 'w') ? i : rw[i + 1];
				ro[i] = (s[i] == 'o') ? i : ro[i + 1];
			}
			cl(g); cl(Sum); int *sum = Sum + 1;
			int Rw, Ro, Lw, Lo, L, R, now = 0, f;
			for (int i = 0; i <= n; ++i) {
				sum[i] = sum[i - 1];
				add(now, g[i]);
				if (i & 1) continue;
				f = now;
				if (i == 0) f = 1;
				if (lw[i] != -1) {
					Lw = lw[i];
					Lo = (lo[Lw] == -1) ? 0 : lo[Lw];
					L = (i - Lw) / 2 + 1;
					if (ro[Lw] != -1 && ro[Lw] <= i)
						L = max(L, i - ro[Lw] + 1);
					R = min(i - Lw, (i - Lo) / 2);
					if (L <= R)
						add(f, (mo + sum[i - 2 * L] - sum[i - 2 * R - 1]) % mo);
				}
				add(sum[i], f);
				Rw = (rw[i + 1] == -1) ? n : rw[i + 1] - 1;
				Ro = (ro[i + 1] == -1) ? n : ro[i + 1] - 1;
				L = 1; R = min((Rw - i) / 2, Ro - i);
				if (L <= R) {
					add(g[i + 2 * R + 1], mo - f);
					add(g[i + 2 * L], f);
				}
				if (i == n) return f;
			}
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
