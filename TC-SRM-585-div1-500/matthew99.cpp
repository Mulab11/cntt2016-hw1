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

const int Mod = 1e9 + 7;

const int maxk = 1300, max0 = 3000;

int n;
int C[max0 + 5][max0 + 5];

inline void prepare()
{
	REP(i, 0, max0 + 1)
	{
		C[i][0] = 1;
		REP(j, 1, i + 1) (C[i][j] = C[i - 1][j - 1] + C[i - 1][j]) %= Mod;
	}
}

class LISNumber 
{
	public:
		int count(vector<int> cardsnum, int K) 
		{
			n = accumulate(ALL(cardsnum), 0);
			prepare();
			static int cnt[maxk + 5];
			REP(i, 1, K + 1)
			{
				cnt[i] = 1;
				for (auto u : cardsnum) cnt[i] = (LL)cnt[i] * C[i][u] % Mod;
			}
			REP(i, 1, K + 1) REP(j, 1, i) (cnt[i] -= (LL)cnt[j] * C[n + i - j][i - j] % Mod) %= Mod;
			int ret = cnt[K];
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
