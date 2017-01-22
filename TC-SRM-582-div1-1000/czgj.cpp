#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int NN = 514114;
const int MM = 23333;
vector<int> dv[MM], f[MM];
bool sq[NN], cb[NN];
int miu[NN];
LL _sqrt(LL x){
	LL l = 0, r = x + 1;
	while (l + 1 < r){
		LL m = (l + r) / 2;
		(x / m / m ? l : r) = m;
	}
	return l;
}
LL _cbrt(LL x){
	LL l = 0, r = x + 1;
	while (l + 1 < r){
		LL m = (l + r) / 2;
		(x / m / m / m ? l : r) = m;
	}
	return l;
}
LL func(LL n){
	LL ret = 0;
	for (LL i = 1; i * i * i <= n; ++i) if (!sq[i]) ret += _sqrt(n / i) - i;
	for (LL i = 1; i * i * i * i <= n; ++i) if (!cb[i])
		rep(j, 1, _cbrt(i)){
			LL k = __gcd(i, (LL)j * j), l = j * j / k, r = _cbrt(n / i) / l;
			if (!sq[i / k])
				for (int d : dv[i / k])
					ret += miu[d] * (f[d][r / d] - f[d][i / l / d]);
		}
	return ret;
}
class SemiPerfectPower {
	public:
	long long count(long long L, long long R) {
		rep(i, 1, MM - 1)
			for (int j = i; j < MM; j += i)
				dv[j].push_back(i);
		for (int i = 2; i * i < NN; ++i){
			for (int t = i * i, j = t; j < NN; j += t) sq[j] = 1;
			for (int t = i * i * i, j = t; j < NN; j += t) cb[j] = 1;
		}
		miu[1] = 1;
		rep(i, 2, MM - 1) miu[i] = sq[i] ? 0 : -miu[i / dv[i][1]];
		rep(i, 1, MM - 1){
			f[i].push_back(0);
			for (int c = 0, j = i; j < NN; j += i)
				f[i].push_back(c += !sq[j]);
		}
		return func(R) - func(L - 1);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 18LL; long long Arg1 = 58LL; long long Arg2 = 9LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 1LL; long long Arg1 = 10LL; long long Arg2 = 3LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 60LL; long long Arg1 = 70LL; long long Arg2 = 1LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 319268319114310LL; long long Arg1 = 35860463407469139LL; long long Arg2 = 95023825161LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 1LL; long long Arg1 = 80000000000000000LL; long long Arg2 = 169502909978LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
	SemiPerfectPower ___test;
	___test.run_test(4);
	 return 0;
}
// END CUT HERE
