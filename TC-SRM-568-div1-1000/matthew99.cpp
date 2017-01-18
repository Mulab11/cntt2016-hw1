#line 5 "DisjointSemicircles.cpp"
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

const int maxn = 50, max0 = 12;

int n, tot = 0, cnt = 0;

int a[maxn + 5];

vector<int> bra[max0 + 1];

inline void prepare()
{
	REP(i, 0, max0 + 1)
		if (!(i & 1))
		{
			bra[i].clear();
			REP(j, 0, 1 << i)
				if (__builtin_popcount(j) == i >> 1)
				{
					bool flag = 1;
					REP(k, 0, i) if ((__builtin_popcount(j >> k) << 1) < (i - k)) { flag = 0; break; }
					if (flag) bra[i].pb(j);
				}
		}
}

vector<int> v[maxn + 5];
int col[maxn + 5];

inline bool dfs(int x) { for (auto y : v[x]) if (~col[y]) { if (col[x] == col[y]) return 0; } else { col[y] = !col[x]; if (!dfs(y)) return 0; } return 1; }

inline bool check()
{
	REP(i, 0, n) v[i].clear();
	static int fir[maxn + 5];
	memset(fir, -1, sizeof fir);
	REP(i, 0, n)
	{
		if (~fir[a[i]])
		{
			static bool sta[maxn + 5];
			memset(sta, 0, sizeof sta);
			REP(j, fir[a[i]] + 1, i) sta[a[j]] ^= 1;
			REP(j, 0, n) if (sta[j]) v[a[i]].pb(j);
		}
		else fir[a[i]] = i;
	}
	memset(col, -1, sizeof col);
	REP(i, 0, n) if (!~col[i] && !(col[i] = 0, dfs(i))) return 0;
	return 1;
}

inline bool work0()
{
	vector<int> all;
	REP(i, 0, n) if (!~a[i]) all.pb(i);
	assert(!(cnt & 1));
	REP(i, 0, 1 << cnt)
	{
		if (i & 1) continue;
		int tmp = __builtin_popcount(i);
		if (tmp & 1) continue;
		for (auto u : bra[tmp])
			for (auto v : bra[cnt - tmp])
			{
				vector<int> stku, stkv;
				int cntu = 0, cntv = 0;
				int now = tot;
				REP(j, 0, cnt)
					if (i >> j & 1)
					{
						if (u >> cntu & 1)
						{
							assert(SZ(stku));
							int tmp = stku.back();
							a[all[j]] = a[all[tmp]] = now++;
							stku.pop_back();
						}
						else stku.pb(j);
						++cntu;
					}
					else
					{
						if (v >> cntv & 1)
						{
							assert(SZ(stkv));
							int tmp = stkv.back();
							a[all[j]] = a[all[tmp]] = now++;
							stkv.pop_back();
						}
						else stkv.pb(j);
						++cntv;
					}
				if (check()) return 1;
			}
	}
	return 0;
}

int fa[maxn + 5];

inline int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

inline bool work1()
{
	REP(i, 0, 1 << tot)
	{
		REP(j, 0, n) fa[j] = j;
		bool flag = 1;
		REP(k, 0, 2)
		{
			static bool vis[maxn + 5];
			static int fir[maxn + 5];
			memset(vis, 0, sizeof vis);
			memset(fir, -1, sizeof fir);
			REP(j, 0, n)
				if (~a[j] && ((i >> a[j] & 1) ^ k))
				{
					if (~fir[a[j]])
					{
						if (vis[fir[a[j]]])
						{
							flag = 0;
							break;
						}
						int lst = -1;
						REP(k, fir[a[j]], j + 1)
						{
							if (!vis[k] && !~a[k])
							{
								if (~lst) fa[get(k)] = get(lst);
								lst = k;
							}
							vis[k] = 1;
						}
					}
					else fir[a[j]] = j;
				}
			int lst = -1;
			REP(j, 0, n) if (!vis[j] && !~a[j]) 
			{
				if (~lst) fa[get(j)] = get(lst);
				lst = j;
			}
			if (!flag) break;
		}
		if (!flag) continue;
		static int num[maxn + 5];
		memset(num, 0, sizeof num);
		REP(j, 0, n) if (!~a[j]) ++num[get(j)];
		REP(j, 0, n) if (num[j] & 1) { flag = 0; break; }
		if (flag) return 1;
	}
	return 0;
}

class DisjointSemicircles
{
	public:
		string getPossibility(vector <int> labels)
		{
			prepare();
			n = SZ(labels);
			copy(ALL(labels), a);
			cnt = 0;
			static int val[maxn + 5];
			memset(val, -1, sizeof val);
			tot = 0;
			REP(i, 0, n) 
			{
				if (~a[i])
				{
					if (!~val[a[i]]) val[a[i]] = tot++;
					a[i] = val[a[i]];
				}
				else ++cnt;
			}
			if (cnt <= max0) return work0() ? "POSSIBLE" : "IMPOSSIBLE";
			return work1() ? "POSSIBLE" : "IMPOSSIBLE";
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
