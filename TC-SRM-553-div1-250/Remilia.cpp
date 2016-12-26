#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define INF 1000000000
#define L(s) (int)((s).size())
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define rept(i,n) FOR(i,0,(n)-1)
#define C(a) memset((a),0,sizeof(a))
#define ll long long
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define VI vector<int>
#define ppb pop_back

VI pr;
ll w;
vector<ll> st;
inline ll pop() {
	// 弹栈
	if (st.empty()) return 0;
	ll t = st.back();
	st.ppb();
	return t;
}
inline ll check(ll x){
	// 模拟
	st.clear();
	vector<int> tpr = pr;
	rept(i, L(pr)) {
		if (tpr[i] == -1) tpr[i] = x;
		if (tpr[i] == 0) {
			ll a = pop();
			ll b = pop();
			st.pb(a + b);
		} else {
			st.pb(tpr[i]);
		}
	}
	return pop();
}
struct Suminator{
	int findMissing( vector <int> program, int wantedResult ){
		pr = program;
		w = wantedResult;
		// 是不是0
		if (check(0) == w) return 0;
		// 是不是1
		if (check(1) == w) return 1;
		// 二分一波，求解
		int l = 0, r = INF + 1;
		while (r - l > 1){
			int xx = (r + l) / 2;
			ll t = check(xx);
			if (t >= w) r = xx; else
			l = xx;
		}
		// xjb判一判边界
		FOR(i, r - 5, r + 5) {
			if (i > 1 && check(i) == w) return i;
		}
		return -1;
	}
};