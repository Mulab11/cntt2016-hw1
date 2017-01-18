#line 5 "StringPath.cpp"
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

const int Mod = 1e9 + 9;

const int oo = 0x3f3f3f3f;

const int maxn = 8;
int pw3[maxn + 1];

class StringPath
{
	public:
		int countBoards(int n, int m, string A, string B)
		{
			pw3[0] = 1;
			REP(i, 0, maxn) pw3[i + 1] = pw3[i] * 3;
			static int dp[1 << (maxn << 1)];
			memset(dp, 0, sizeof dp);
			dp[3] = 1;
			REP(i, 0, n) REP(j, 0, m) 
			{
				static int nxt[1 << (maxn << 1)];
				memset(nxt, 0, sizeof nxt);
				REP(k, 0, 1 << (m << 1))
					if (dp[k] && (k & 0x5555555) && (k & 0xaaaaaaaa))
					{
						bool canA = (k >> (j << 1) & 1), canB = (k >> (j << 1) & 2);
						if (j) canA |= (k >> ((j - 1) << 1) & 1), canB |= (k >> ((j - 1) << 1) & 2);
						int tmp = k & (((1 << (m << 1)) - 1) ^ (1 << (j << 1)) ^ (1 << (j << 1 | 1)));
						if (A[i + j] == B[i + j]) 
						{
							(nxt[tmp | (canA << (j << 1)) | (canB << (j << 1 | 1))] += dp[k]) %= Mod;
							(nxt[tmp] += (LL)dp[k] * 25 % Mod) %= Mod;
						}
						else
						{
							(nxt[tmp | (canA << (j << 1))] += dp[k]) %= Mod;
							(nxt[tmp | (canB << (j << 1 | 1))] += dp[k]) %= Mod;
							(nxt[tmp] += (LL)dp[k] * 24 % Mod) %= Mod;
						}
					}
				memcpy(dp, nxt, sizeof dp);
			}
			int ret = 0;
			REP(i, 0, 1 << (m << 1)) if ((i >> ((m - 1) << 1)) == 3) (ret += dp[i]) %= Mod;
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
