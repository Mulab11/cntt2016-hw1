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

class ICPCBalloons 
{
	public:
		int minRepaintings(vector<int> num, string col, vector<int> a) 
		{
			vector<int> bln[2];
			int m = SZ(num);
			REP(i, 0, m)
			{
				if (col[i] == 'M') bln[0].pb(num[i]);
				else bln[1].pb(num[i]);
			}
			REP(i, 0, 2) sort(ALL(bln[i]), greater<int>());
			int n = SZ(a);
			int ret = oo;
			REP(i, 0, 1 << n)
			{
				vector<int> pro[2];
				int sum = 0;
				REP(j, 0, n) pro[i >> j & 1].pb(a[j]), sum += a[j];
				REP(j, 0, 2)
				{
					sort(ALL(pro[j]), greater<int>());
					if (accumulate(ALL(pro[j]), 0) > accumulate(ALL(bln[j]), 0)) { sum = oo; break; }
					REP(k, 0, min(SZ(bln[j]), SZ(pro[j]))) sum -= min(bln[j][k], pro[j][k]);
				}
				chkmin(ret, sum);
			}
			if (ret >= oo) return -1;
			return ret;
		}
};

// Powered by Greed 2.0-RC
