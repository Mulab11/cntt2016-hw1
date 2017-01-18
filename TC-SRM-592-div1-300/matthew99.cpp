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

int calc(const string &u)
{
	set<char> all;
	for (auto x : u) all.insert(x);
	return SZ(all);
}

class LittleElephantAndBalls 
{
	public:
		int getNumber(string S) 
		{
			string now;
			int ret = 0;
			for (auto u : S)
			{
				int Max = -1, Maxp = -1;
				REP(i, 0, SZ(now) + 1) if (chkmax(Max, calc(now.substr(0, i)) + calc(now.substr(i)))) Maxp = i;
				now = now.substr(0, Maxp) + u + now.substr(Maxp);
				ret += Max;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
