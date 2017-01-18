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

const double eps = 1e-8;

inline int dcmp(double x) { return x < -eps ? -1 : x > eps; }

struct point
{
	int x, y;

	point() { }
	point(const int &_x, const int &_y): x(_x), y(_y) { }

	friend point operator+(const point &x, const point &y) { return point(x.x + y.x, x.y + y.y); }
	friend point &operator+=(point &x, const point &y) { x.x += y.x, x.y += y.y; return x; }
	friend point operator-(const point &x, const point &y) { return point(x.x - y.x, x.y - y.y); }
	friend point &operator-=(point &x, const point &y) { x.x -= y.x, x.y -= y.y; return x; }
	friend bool operator<(const point &x, const point &y) { if (!dcmp(x.x - y.x)) return dcmp(x.y - y.y) < 0; return x.x < y.x; }
	friend LL operator*(const point &x, const point &y) { return (LL)x.x * y.x + (LL)x.y * y.y; }
	friend LL operator^(const point &x, const point &y) { return (LL)x.x * y.y - (LL)x.y * y.x; }

};

const int maxm = 60000, maxn = 22;

int m, N, n;
point a[(maxm << 3) + 5], b[maxn + 5];
int pre[(maxm << 3) + 5], nxt[(maxm << 3) + 5];
LL sum[(maxm << 3) + 5];;

inline bool can(int x, int y)
{
	REP(i, 0, n) if (((a[y] - a[x]) ^ (b[i] - a[x])) < 0) 
	{
		return 0;
	}
	return 1;
}

class EnclosingTriangle 
{
	public:
		long long getNumber(int m, vector<int> x, vector<int> y) 
		{
			::m = m;
			N = 0;
			REP(i, 0, m) a[N++] = point(i, 0);
			REP(i, 0, m) a[N++] = point(m, i);
			for (int i = m; i >= 1; --i) a[N++] = point(i, m);
			for (int i = m; i >= 1; --i) a[N++] = point(0, i);
			REP(i, 0, N) a[N + i] = a[i];
			n = SZ(x);
			REP(i, 0, n) b[i] = point(x[i], y[i]);
			int j = 0;
			REP(i, 0, N << 1)
			{
				while (j < i && !can(j, i)) ++j;
				pre[i] = j;
			}
			j = (N << 1) - 1;
			for (int i = (N << 1) - 1; i >= 0; --i)
			{
				while (j > i && !can(i, j)) --j;
				nxt[i] = j;
			}
			sum[0] = 0;
			REP(i, 0, N) sum[i + 1] = sum[i] + (i + N - pre[i + N]);
			REP(i, N, N << 1) sum[i + 1] = sum[i] + (i - pre[i]);
			LL ret = 0;
			REP(i, 0, N)
			{
				int x = i;
				if (pre[x + N] < N) x += N;
				int u = pre[x], v = nxt[x];
				int w = v >= N ? nxt[v - N] : nxt[v] - N;
				if (w >= u)
				{
					int cnt = w - u + 1;
					ret += sum[w + 1] - sum[u] - ((LL)N * cnt - ((LL)(v + 1) * cnt - ((LL)(u + w) * cnt >> 1)));
				}
			}
			assert(!(ret % 3));
			ret /= 3;
			REP(i, 0, N) if (nxt[nxt[i] % N] % N == i) --ret;
			return ret;
		}
};

// Powered by Greed 2.0-RC
