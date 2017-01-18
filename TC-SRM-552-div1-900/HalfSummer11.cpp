#line 2 "HolyNumbers.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 1000010
typedef long long ll;
using namespace std;
bool np[maxn], flag;
int n, tot;
ll ans, lim, p[maxn];
void sieve(int n) { // 筛出质数
	np[1] = 1; tot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!np[i]) p[++tot] = i;
		for (int j = 1; j <= tot && i * p[j] <= n; ++j) {
			np[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
ll dfs(int num, ll rest) { // dfs(num, rest) 表示大小在rest之内的，是若干标号大于等于num的质数的奇数幂之积的数的个数
	if (rest < p[num] || num > tot) return 0;
	ll ret = 0;
	if (p[num] * p[num] >= rest) return ret = upper_bound(p + num, p + tot + 1, rest) - p - num; // 若小于p[num] ^ 2,就只能再放下一个质数，方案数就是不超过它的质数的个数
	ret += dfs(num + 1, rest); // 否则，一种可能是跳过这个质数不选
	for (ll tmp = rest / p[num]; tmp; tmp /= p[num] * p[num]) // 一种可能是包含这个质数的一个奇数幂
		ret += dfs(num + 1, tmp) + 1; // 这里的1表示不再乘后面的质数，得到的数字
	return ret;
}
class HolyNumbers {
	public:
		long long count(long long lim, int n) {
			sieve(n);
			return dfs(1, lim) + 1;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10LL; int Arg1 = 100; long long Arg2 = 8LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 10LL; int Arg1 = 3; long long Arg2 = 5LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 123LL; int Arg1 = 12; long long Arg2 = 32LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 123LL; int Arg1 = 456; long long Arg2 = 88LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 123456789LL; int Arg1 = 12345; long long Arg2 = 25994500LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	HolyNumbers ___test;
	___test.run_test(-1);
	system("pause");
}
// END CUT HERE
