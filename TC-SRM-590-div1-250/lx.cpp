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

class FoxAndChess {
private :
	int n;
public :
	//模拟
	string ableToMove(string A, string B) {
		n = A.size();
		int j = 0;
		rep (i, 0, n-1) {
			if (A[i] != '.') {
				while (j < n && B[j] == '.') ++j;
				if (j == n || A[i] != B[j] || (A[i] == 'L' && i < j) || (A[i] == 'R' && i > j)) {
					return "Impossible";
				}
				++j;
			}
		}
		while (j < n) {
			if (B[j] != '.') {
				return "Impossible";
			}
			++j;
		}
		return "Possible";
	}
};
