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

string to_str(int x)
{
	ostringstream o;
	o << x;
	return o.str();
}

class TheNumberGame 
{
	public:
		string determineOutcome(int A, int B) 
		{
			string a = to_str(A);
			string b = to_str(B);
			if (a.find(b) != string::npos) return "Manao wins";
			reverse(ALL(b));
			if (a.find(b) != string::npos) return "Manao wins";
			return "Manao loses";
		}
};

// Powered by Greed 2.0-RC
