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

class FoxAndMountainEasy 
{
	public:
		string possible(int n, int h0, int hn, string a) 
		{
			if ((h0 ^ hn ^ n) & 1) return "NO";
			int sum = h0;
			int Max = 0;
			for (auto u : a) 
			{
				if (u == 'D') --sum;
				else ++sum;
				chkmax(Max, -sum);
			}
			n -= SZ(a) + Max;
			sum += Max;
			if (abs(hn - sum) > n) return "NO";
			return "YES";
		}
};

// Powered by Greed 2.0-RC
