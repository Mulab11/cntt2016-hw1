#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class PointyWizardHats {
private :
	struct data {
		int h, r, v;
		data() {}
		data(int h, int r, int v) : h(h), r(r), v(v) {}
		inline bool operator < (const data &b) const {
			return (r * b.h < b.r * h) || (r * b.h == b.r * h && v < b.v);
		}
	};
	vector<data> P;
public :
	//STL 应用题
	int getNumHats(vector<int> A, vector<int> B, vector<int> X, vector<int> Y) {
		rep (i, 0, A.size()-1) {
			P.pb(data(A[i], B[i], 1));
		}
		rep (i, 0, X.size()-1) {
			P.pb(data(X[i], Y[i], 0));
		}
		sort(P.begin(), P.end());
		int ans = 0;
		multiset<int> S;
		rep (i, 0, P.size()-1) {
			if (P[i].v) {
				S.insert(P[i].r);
			} else {
				multiset<int>::iterator u = S.upper_bound(P[i].r);
				if (u != S.begin()) {
					S.erase(--u);
					ans++;
				}
			}
		}
		return ans;
	}
};
