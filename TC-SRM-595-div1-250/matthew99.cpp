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

const int maxn = 52, maxm = 1010;

int c[maxm + 5];
bool vis[maxn + 5];

class LittleElephantAndIntervalsDiv1
{
	public:
	LL getNumber(int M, vector<int> L, vector<int> R)
	{
		memset(c, -1, sizeof c);
		REP(i, 0, SZ(L)) 
		{
			--L[i], --R[i];
			REP(j, L[i], R[i] + 1) c[j] = i;
		}
		memset(vis, 0, sizeof vis);
		REP(i, 0, M) vis[c[i]] = 1;
		return 1LL << accumulate(vis, vis + SZ(L), 0);
	}
};
