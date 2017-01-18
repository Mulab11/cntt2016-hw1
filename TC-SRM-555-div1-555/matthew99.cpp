#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
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

const int Mod = 555555555;

int C[maxn + 5][maxn + 5];

inline void prepare()
{
	REP(i, 0, maxn + 1)
	{
		C[i][0] = 1;
		REP(j, 1, i + 1) (C[i][j] = C[i - 1][j - 1] + C[i - 1][j]) %= Mod;
	}
}

inline int calc(int x, int y) { if (!x && !y) return 1; return C[x + y - 1][y]; }

class XorBoard 
{
	public:
		int count(int H, int W, int Rcount, int Ccount, int S) 
		{
			prepare();
			int ret = 0;
			REP(i, 0, H + 1) REP(j, 0, W + 1)
			{
				int num = i * W + H * j - ((i * j) << 1);
				if (num == S && i <= Rcount && !((i ^ Rcount) & 1) && !((j ^ Ccount) & 1)) (ret += (LL)C[H][i] * C[W][j] % Mod * calc(H, (Rcount - i) >> 1) % Mod * calc(W, (Ccount - j) >> 1) % Mod) %= Mod;
			}
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
