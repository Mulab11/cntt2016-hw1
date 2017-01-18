#line 5 "FoxAndAvatar.cpp"
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

const int maxn = 3000;

int N, m;

inline bool in(const pair<int, int> &x, int l0, int r0, int l1, int r1)
{
	return x.x >= l0 && x.x < r0 && x.y >= l1 && x.y < r1;
}

inline void get(pair<int, int> *a, int n)
{
	a[0] = mp(0, 0);
	REP(i, 1, n) 
	{
		a[i] = a[i - 1];
		++a[i].y;
		if (a[i].y == m) a[i].y = 0, ++a[i].x;
	}
}

inline bool check(int n, int x)
{
	if (n <= m && (!x || x == n - 1)) return 1;
	if (x == m - 1 && n < (m << 1)) return 1;
	if (x == n - 1 && !(x % m)) return 1;
	return 0;
}

inline int calc(int n, int x)
{
	if (n == 1) return 0;
	if (check(n, x)) return 1;
	static pair<int, int> a[maxn + 5];
	get(a, n);
	static vector<int> sum0[maxn + 5], sum1[maxn + 5];
	REP(i, 0, N + 1)
	{
		sum0[i] = vector<int>(m + 1, 0);
		sum1[i] = vector<int>(m + 1, 0);
	}
	REP(i, 0, x) sum0[a[i].x + 1][a[i].y + 1] = 1;
	REP(i, 0, n) sum1[a[i].x + 1][a[i].y + 1] = 1;
	REP(i, 0, N) REP(j, 0, m) sum0[i + 1][j + 1] += sum0[i + 1][j] + sum0[i][j + 1] - sum0[i][j];
	REP(i, 0, N) REP(j, 0, m) sum1[i + 1][j + 1] += sum1[i + 1][j] + sum1[i][j + 1] - sum1[i][j];
	REP(i, 0, n)
	{
		int l0, r0, l1, r1;
		REP(j, 0, 4)
		{
			if (j & 1) r0 = a[x].x;
			else r0 = N;
			if (j >> 1) l1 = 0;
			else l1 = a[x].y + 1;
			r1 = l1 + i;
			if (r1 > m) continue;
			for (l0 = 0; l0 < r0; ++l0)
			{
				if (l0 >= r0 || l1 >= r1) continue;
				if (in(a[x], l0, r0, l1, r1)) continue;
				int newx = x - (sum0[r0][r1] - sum0[l0][r1] - sum0[r0][l1] + sum0[l0][l1]);
				int newn = n - (sum1[r0][r1] - sum1[l0][r1] - sum1[r0][l1] + sum1[l0][l1]);
				if (check(newn, newx)) return 2;
			}
		}
	}
	return 3;
}

class FoxAndAvatar
{
	public:
		int minimalSteps(int n, int _m, int x)
		{
			m = _m;
			N = (n + m - 1) / m;
			--x;
			if (n == 1) return 0;
			if (check(n, x)) return 1;
			static pair<int, int> a[maxn + 5];
			get(a, n);
			int ans = 4;
			REP(i, 1, m + 1)
			{
				int l0, r0, l1, r1;
				REP(j, 0, 4)
				{
					if (j & 1) r0 = a[x].x;
					else r0 = N;
					if (j >> 1) l1 = 0;
					else l1 = a[x].y + 1;
					r1 = l1 + i;
					if (r1 > m) continue;
					for (l0 = 0; l0 < r0; ++l0)
					{
						if (l0 >= r0 || l1 >= r1) continue;
						if (in(a[x], l0, r0, l1, r1)) continue;
						int cnt = 0;
						int p = 0;
						REP(k, 0, n) if (!in(a[k], l0, r0, l1, r1))
						{
							++cnt;
							if (k < x) ++p;
						}
						chkmin(ans, calc(cnt, p) + 1);
					}
				}
			}
			return ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
