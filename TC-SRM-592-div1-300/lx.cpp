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

class LittleElephantAndBalls {
public :
	//贪心，构造
	int getNumber(string S) {
		set<char> L, R;
		int ans = 0;
		rep (i, 0, S.size()-1) {
			ans += L.size() + R.size();
			(L.count(S[i]) ? R : L).insert(S[i]);
		}
		return ans;
	}
};
