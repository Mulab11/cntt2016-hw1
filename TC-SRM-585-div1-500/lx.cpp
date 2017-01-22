#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))

using namespace std;
typedef long long LL;

const int mo = 1e9 + 7;
const int N = 1297;

inline int inc(int x, int y) {
	return (x += y) >= mo ? x - mo : x;
}
inline void upd(int &x, int y) {
	(x += y) >= mo ? x -= mo : 0;
}

class LISNumber {
private :
	int C[N][N], f[2][N];
public :
	int count(vector<int> cards, int K) {
		int t = 0, tot = cards[0];
		f[t][tot - 1] = 1;
		C[0][0] = 1;
		rep (i, 1, 1296) {
			C[i][0] = 1;
			rep (j, 1, i) 
				C[i][j] = inc(C[i - 1][j], C[i - 1][j - 1]);
		}
		rep (i, 1, cards.size() - 1) {
			memset(f[t ^ 1], 0, sizeof(f[t ^ 1]));
			int v = cards[i];
			rep (j, 0, tot) if (f[t][j]) {
				int x = f[t][j];
				rep (k, 0, v) {
					int p = C[j+1][v-k], q = C[tot-j+v-1][k];
					upd(f[t ^ 1][j + k], (LL)x * p % mo * q % mo);
				}
			}
			tot += v;
			t ^= 1;
		}
		return f[t][K - 1];
	}
};
