/*
	Two brute forces
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
string st;
int n, t, m;
int func1(const string &st){
	int dp[2] = {0, 0};
	rep(i, 1, t){
		int cnt[2] = {0, 0};
		rep(j, (i - 1) * m, i * m - 1) cnt[st[j] & 1]++;
		int t0 = min(cnt[1] + dp[0], 1 + cnt[0] + dp[1]);
		int t1 = min(cnt[0] + dp[1], 1 + cnt[1] + dp[0]);
		dp[0] = t0, dp[1] = t1;
	}
	int ret = dp[0];
	rep(i, t * m, n - 1) ret += st[i] & 1;
	return ret;
}
int solve1(){ // enumerate the string
	int ret = 666;
	string t(n, '0');
	rep(i, 0, (1 << m) - 1){
		rep(j, 0, n - 1) t[j] = (i >> (j % m) & 1) ^ st[j];
		ret = min(ret, func1(t));
	}
	return ret;
}
int func2(const string &st){
	int ret = 0;
	rep(i, 0, m - 1){
		int cnt[2] = {0, 0};
		for (int j = i; j < n; j += m)
			cnt[st[j] & 1]++;
		ret += min(cnt[0], cnt[1]);
	}
	return ret;
}
int solve2(){ // enumerate the m-flips
	int ret = 666;
	string s;
	rep(i, 0, (1 << t) - 1){
		s = st; bool p = 0;
		red(j, t - 1, 0){
			p ^= i >> j & 1;
			if (p) rep(k, j * m, (j + 1) * m - 1) s[k] ^= 1;
		}
		ret = min(ret, func2(s) + __builtin_popcount(i));
	}
	return ret;
}
class FlippingBitsDiv1 {
	public:
	int getmin(vector <string> S, int m) {
		st = ""; rep(i, 0, (int)S.size() - 1) st += S[i];
		::m = m, n = st.size(), t = n / m;
		return m <= 17 ? solve1() : solve2();
	}
};

/*
	Chocobo
*/
