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

class MayTheBestPetWin {
private :
	bitset<1000005> Pack;
	int n;
public :
	// 01背包，数学推导
	int calc(vector<int> A, vector<int> B) {
		n = A.size();
		int sa = 0, sb = 0;
		Pack[0] = 1;
		rep (i, 0, n-1) {
			sa += A[i];
			sb += B[i];
			Pack |= Pack << (A[i] + B[i]);
		}
		int res = inf;
		rep (i, 0, sa + sb) {
			if (Pack[i]) {
				upmin(res, max(sb - i, i - sa));
			}
		}
		return res;
	}
};

