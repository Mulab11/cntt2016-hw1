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

int num[26];
int cnt[26];

class FoxAndHandle 
{
	public:
		string lexSmallestName(string S) 
		{
			int n = SZ(S);
			memset(num, 0, sizeof num);
			for (auto u : S) ++num[u - 'a'];
			REP(i, 0, 26) cnt[i] = num[i] >>= 1;
			string ret;
			int k = 0;
			static int ret_cnt[26];
			memset(ret_cnt, 0, sizeof ret_cnt);
			REP(i, 0, n >> 1)
			{
				static int tmp[26];
				memset(tmp, 0, sizeof tmp);
				int l = k;
				int Minp = -1;
				while (l < n)
				{
					if (ret_cnt[S[l] - 'a'] < num[S[l] - 'a'] && (!~Minp || S[l] < S[Minp])) Minp = l;
					++tmp[S[l] - 'a'];
					if (tmp[S[l] - 'a'] > cnt[S[l] - 'a']) break;
					++l;
				}
				++ret_cnt[S[Minp] - 'a'];
				while (k < Minp) --cnt[S[k] - 'a'], ++k;
				++k;
				ret += S[Minp];
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
