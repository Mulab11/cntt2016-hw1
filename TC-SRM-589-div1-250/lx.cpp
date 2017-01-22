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

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

class GooseTattarrattatDiv1 {
private :
	int fa[N], mx[N];
	inline int findSet(int x) {
		return fa[x] == x ? x : fa[x] = findSet(fa[x]);
	}
	int n;
public :
	int getmin(string S) {
		n = S.size();
		rep (i, 0, n-1)  ++mx[S[i] - 'a'];
		rep (i, 0, 25)  fa[i] = i;
		rep (i, 0, (n-1)/2) {
			int x = findSet(S[i] - 'a');
			int y = findSet(S[n-i-1] - 'a');
			if (x != y) {
				fa[y] = x;
				upmax(mx[x], mx[y]);
			}
		}
		int ans = n;
		rep (i, 0, 25) {
			if (fa[i] == i) {
				ans -= mx[i];
			}
		}
		return ans;
	}
};
