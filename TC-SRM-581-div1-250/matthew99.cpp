#line 5 "SurveillanceSystem.cpp"
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

const int maxn = 50;

int n;
bool g[maxn + 5];

int cnt[maxn + 5];
int tot[maxn + 5];

bool can[maxn + 5], must[maxn + 5];

class SurveillanceSystem
{
	public:
		string getContainerInfo(string containers, vector <int> reports, int L)
		{
			memset(tot, 0, sizeof tot);
			memset(can, 0, sizeof can);
			memset(must, 0, sizeof must);
			for (auto x : reports) ++tot[x];
			n = SZ(containers);
			REP(i, 0, n) g[i] = containers[i] == 'X';
			REP(i, 0, n - L + 1)
			{
				cnt[i] = 0;
				REP(j, i, i + L) cnt[i] += g[j];
				if (tot[cnt[i]]) REP(j, i, i + L) can[j] = 1;
			}
			REP(i, 0, n)
			{
				static int num[maxn + 5];
				memset(num, 0, sizeof num);
				REP(j, 0, n - L + 1) if (j > i || j + L <= i) ++num[cnt[j]];
				REP(j, 0, L + 1) if (num[j] < tot[j]) { must[i] = 1; break; }
			}
			string ret;
			REP(i, 0, n) if (must[i]) ret += '+'; else if (can[i]) ret += '?'; else ret += '-';
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
