/*
	f**king dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;
const int MAXN = 2020202;
int f[MAXN], g[MAXN], prew[MAXN], preo[MAXN], nxtw[MAXN], nxto[MAXN];
string s;
class WolfDelaymasterHard {
	public:
	int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
		memset(f, 0, sizeof f); memset(g, 0, sizeof g);
		// generate
		s = string(N + 2, '?');
		LL x = w0; rep(i, 1, wlen) s[x + 1] = 'w', x = (x * wmul + wadd) % N;
		x = o0; rep(i, 1, olen) s[x + 1] = 'o', x = (x * omul + oadd) % N;
		// pre-process
		nxtw[N + 1] = nxto[N + 1] = N + 1; prew[0] = preo[0] = -1;
		red(i, N, 0) nxtw[i] = (s[i] == 'w' ? i : nxtw[i + 1]), nxto[i] = (s[i] == 'o' ? i : nxto[i + 1]);
		rep(i, 1, N) prew[i] = (s[i] == 'w' ? i : prew[i - 1]), preo[i] = (s[i] == 'o' ? i : preo[i - 1]);
		int u, v; f[0] = 1; v = min(nxto[0] - 1, (nxtw[0] - 1) / 2);
		if (v >= 1) g[2] = 1, g[2 * v + 1] = MOD - 1;
		rep(i, 1, N + 1){ // f**king dp
			g[i] = (g[i] + g[i - 1]) % MOD;
			if (i % 2 == 0){
				f[i] = g[i];
				u = max((i - prew[i]) / 2 + 1, i - nxto[prew[i]] + 1);
				v = min(i - prew[i], (i - preo[prew[i]]) / 2);
				if (u <= v) f[i] = ((LL)f[i] + f[i - 2 * u] + (i >= 2 * v + 1 ? MOD - f[i - 2 * v - 1] : 0)) % MOD;
				v = min(nxto[i + 1] - i - 1, (nxtw[i + 1] - i - 1) / 2);
				if (v >= 1) g[i + 2] = (g[i + 2] + f[i]) % MOD, g[i + 2 * v + 1] = (g[i + 2 * v + 1] - f[i] + MOD) % MOD;
			}
			f[i] = (f[i - 1] + f[i]) % MOD;
		}
		return (f[N] - f[N - 1] + MOD) % MOD;
	}
};

/*
	I'm really tired of debugging it....
	Thx RXDoi wwwww
*/
