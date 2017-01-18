#line 5 "TheBrickTowerHardDivOne.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const LL Mod = 1234567891;

const int max0 = 120;

LL f[max0 + 5][max0 + 5];

int tot = 0;
int id[5][5][5][5];
int cnt[max0];

int C, K;

int a[8];

void dfs(int x)
{
	if (x == 8)
	{
		int from = id[a[0]][a[1]][a[2]][a[3]];
		if (from == -1) return;
		int b[] = {a[4], a[5], a[6], a[7]};
		int h[8];
		memset(h, -1, sizeof h);
		int cur = 0;
		REP(i, 0, 4) 
		{
			if (h[b[i]] == -1) h[b[i]] = cur++;
			b[i] = h[b[i]];
		}
		int to = id[b[0]][b[1]][b[2]][b[3]];
		if (to == -1) return;
		int lo = 0, hi = 0;
		REP(i, 0, 8)
		{
			chkmax(hi, a[i]);
			if (i < 4) chkmax(lo, a[i]);
		}
		LL num = 1;
		if (hi >= C) return;
		REP(i, lo + 1, hi + 1) (num *= (C - i)) %= Mod;
		int delta = cnt[to];
		REP(i, 0, 4) delta += a[i] == a[i + 4];
		REP(i, 0, K - delta + 1) (f[from * (K + 1) + i][to * (K + 1) + i + delta] += num) %= Mod;
		return;
	}
	if (!x) a[x] = 0, dfs(x + 1);
	else
	{
		int Min = oo, Max = 0;
		REP(i, 0, x) chkmin(Min, a[i]), chkmax(Max, a[i]);
		REP(i, Min, Max + 2) a[x] = i, dfs(x + 1);
	}
}

bool ok[max0 + 5];
LL beg0[max0 + 5];
int col[max0 + 5];

const int max1 = 120;

int N;
LL beg[max1 + 5];
LL g[max1 + 5][max1 + 5];

inline void minimize()
{
	memset(ok, 0, sizeof ok);
	REP(i, 0, tot) REP(j, cnt[i], K + 1) ok[i * (K + 1) + j] = 1;
	static const int hash_Mod = 1e9 + 9, hash_mul = 998244353;
	int M = tot * (K + 1);
	int lst = 0;
	REP(i, 0, M) if (ok[i]) col[i] = 0;
	N = 1;
	while (1)
	{
		static int val[max0 + 5];
		vector<int> v;
		lst = N;
		REP(i, 0, M)
			if (ok[i])
			{
				static LL all[max0 + 5];
				memset(all, 0, sizeof all);
				REP(j, 0, M) if (ok[j]) (all[col[j]] += f[i][j]) %= hash_Mod;
				val[i] = 0;
				REP(j, 0, N) val[i] = ((LL)val[i] * hash_mul + all[j]) % hash_Mod;
				v.pb(val[i]);
			}
		sort(ALL(v));
		v.resize(unique(ALL(v)) - v.begin());
		N = SZ(v);
		REP(i, 0, M) if (ok[i]) col[i] = lower_bound(ALL(v), val[i]) - v.begin();
		if (N == lst) break;
	}
	memset(g, 0, sizeof g);
	memset(beg, 0, sizeof beg);
	static bool vis[max1 + 5];
	memset(vis, 0, sizeof vis);
	REP(i, 0, M) if (ok[i])
	{
		(beg[col[i]] += beg0[i]) %= Mod;
		if (vis[col[i]]) continue;
		vis[col[i]] = 1;
		REP(j, 0, M) if (ok[j]) (g[col[i]][col[j]] += f[i][j]) %= Mod;
	}
	++N;
	REP(i, 0, N) g[i][N - 1] = 1;
}

inline void mul(LL a[max1 + 5][max1 + 5], LL b[max1 + 5][max1 + 5])
{
	static LL ans[max1 + 5][max1 + 5];
	memset(ans, 0, sizeof ans);
	REP(i, 0, N) REP(j, 0, N) REP(k, 0, N)
		(ans[i][k] += a[i][j] * b[j][k] % Mod) %= Mod;
	REP(i, 0, N) REP(j, 0, N) a[i][j] = ans[i][j];
}

class TheBrickTowerHardDivOne
{
	public:
		int find(int C, int K, long long H)
		{
			::C = C, ::K = K;
			memset(f, 0, sizeof f);
			memset(beg0, 0, sizeof beg0);
			tot = 0;
			memset(id, -1, sizeof id);
			REP(a, 0, 1) REP(b, a, min(4, a + 2)) REP(c, min(a, b), min(4, max(a, b) + 2)) REP(d, min(a, min(b, c)), min(4, max(a, max(b, c)) + 2)) 
			{
				int num = max(max(a, b), max(c, d));
				cnt[tot] = (a == b) + (a == c) + (c == d) + (b == d);
				if (cnt[tot] > K) continue;
				id[a][b][c][d] = tot;
				if (num < C)
				{
					LL tmp = 1;
					REP(j, 0, num + 1) (tmp *= C - j) %= Mod;
					beg0[tot * (K + 1) + cnt[tot]] = tmp;
				}
				++tot;
			}
			dfs(0);
			minimize();
			static LL tmp[max1 + 5][max1 + 5];
			memset(tmp, 0, sizeof tmp);
			REP(i, 0, N) tmp[i][i] = 1;
			LL u = H;
			for ( ; u; u >>= 1, mul(g, g))
				if (u & 1) mul(tmp, g);
			LL ret = 0;
			REP(i, 0, N) if (beg[i]) (ret += beg[i] * tmp[i][N - 1] % Mod) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
