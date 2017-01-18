#line 2 "HatRack.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
int n, g[maxn], ei;
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int l[maxn], r[maxn], pre[maxn], size[maxn], cnt2[maxn];
int idx, leaf;
bool dfs(int x) {
	bool ret = 1; int son = 0; size[x] = 1;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			++son; pre[e[i].t] = x; 
			ret &= dfs(e[i].t);
			size[x] += size[e[i].t];
			if (son > 2) return 0;
		}
	return ret;
}
void label(int x, int num) {
	idx = max(idx, num);
	if (num == n) leaf = x;
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			if (!l[x]) l[x] = e[i].t; else r[x] = e[i].t;
		}
	if (l[x] && r[x] && (size[l[x]] < size[r[x]])) swap(l[x], r[x]);
	if (l[x] && r[x]) cnt2[x] = 1;
	if (l[x]) label(l[x], num << 1), cnt2[x] += cnt2[l[x]];
	if (r[x]) label(r[x], (num << 1) | 1), cnt2[x] += cnt2[r[x]];
}
class HatRack {
	public:
		long long countWays(vector <int> x, vector <int> y) {
			n = x.size() + 1;
			cl(g); ei = 0;
			for (int i = 0; i < n - 1; ++i) 
				ae(x[i], y[i]), ae(y[i], x[i]);
			ll sum = 0;
			for (int i = 1; i <= n; ++i) {
				cl(pre); cl(l); cl(r);
				if (dfs(i)) {
					cl(cnt2); idx = 0; label(i, 1);
					if (idx > n) continue;
					int now = leaf; ll ans = 1;
					while (pre[now] && r[pre[now]] == now) {
						ans = ans * ans * 2ll; now = pre[now];
					}
					int last = now; now = pre[now];
					while (now) { 
						if (l[now] == last) {
							if (r[now]) ans <<= (ll)cnt2[r[now]];
						} else {
							ans <<= (ll)cnt2[l[now]];
						}
						last = now; now = pre[now];
					}
					sum += ans;
				}
			}
			return sum;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 9, 4, 7, 6, 8, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 1, 5, 9, 5, 9, 1, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,6,6,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,4,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,2,2,11,11,8,8,3,3,4,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,11,8,12,13,9,10,4,5,7,6,14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 16LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
 	HatRack ___test;
	int x;
	cin >> x;
	___test.run_test(x);
	system("pause");
}
// END CUT HERE
