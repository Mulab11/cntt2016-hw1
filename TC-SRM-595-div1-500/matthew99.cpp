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

const int maxn = 2550;

int n;
string s;

int fen[maxn + 5];

inline void add(int x, int c)
{
	for (int i = x + 1; i <= n; i += i & -i) fen[i] += c;
}

inline int query(int x)
{
	int ret = 0;
	for (int i = x; i; i -= i & -i) ret += fen[i];
	return ret;
} 

class LittleElephantAndRGB 
{
	public:
		LL getNumber(vector<string> list, int m)
		{
			memset(fen, 0, sizeof fen);
			s = accumulate(ALL(list), string());
			n = SZ(s);
			LL ret = 0;
			int le = 0;
			REP(i, 0, n)
			{
				int fir = 0, cur = 0, find = 0;
				for (int j = i; j >= 0; --j)
				{
					if (s[j] == 'G')
					{
						if (fir == i - j) ++fir;
						++cur;
					}
					else cur = 0;
					find |= cur >= m;
					if (find) ++le;
					else add(m - fir, 1);
				}
				fir = cur = find = 0;
				REP(j, i + 1, n)
				{
					if (s[j] == 'G')
					{
						if (fir == j - i - 1) ++fir;
						++cur;
					}
					else cur = 0;
					find |= cur >= m;
					ret += le;
					if (find) ret += query(m + 1);
					else ret += query(fir + 1);
				}
			}
			return ret;
		}

};



// Powered by Greed 2.0-RC
