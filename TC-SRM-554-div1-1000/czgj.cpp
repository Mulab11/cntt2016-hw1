#include <bits/stdc++.h>
#define rep(i, l, r) for (int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for (int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << (x) << endl
#define MEM(x, y) memset(x, y, sizeof x)
using namespace std;
typedef long long LL;
const int MAXM = 123;
const int MAXN = 6666;
const LL MOD = 1234567891;
int n;
struct Laevatain {
	LL a[MAXM][MAXN];
	void biu(bool f = 0){
		memset(a, 0, sizeof a);
		if (f) rep(i, 0, n) a[i][i] = 1;
	}
	LL* operator[](int x) const {
		return (LL*)a[x];
	}
};
Laevatain operator *(const Laevatain &a, const Laevatain &b) {
	static Laevatain c; c.biu(0);
	rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) c[i][k] = (c[i][k] + a[i][j] * b[j][k]) % MOD; 
	return c;
}
Laevatain extend(Laevatain x, LL y){
	static Laevatain c; c.biu(1);
	for (; y; y >>= 1, x = x * x)
		if (y & 1) c = c * x;
	return c;
}
const int Bomb[][4] = {{1, 1, 1, 1}, {1, 1, 1, 2}, {1, 1, 2, 1}, {1, 1, 2, 2}, {1, 1, 2, 3}, {1, 2, 1, 1}, {1, 2, 1, 2}, {1, 2, 1, 3}, {1, 2, 2, 1}, {1, 2, 2, 2}, {1, 2, 2, 3}, {1, 2, 3, 1}, {1, 2, 3, 2}, {1, 2, 3, 3}, {1, 2, 3, 4}};
LL Power[MAXN][10];
class TheBrickTowerHardDivOne {
	public:
	TheBrickTowerHardDivOne() {
		rep(i, 0, 5000) rep(j, 0, min(5, i)) Power[i][j] = j ? Power[i][j - 1] * (i - j + 1) % MOD : 1;
	}
	Laevatain A0, v0;
	int col, k;
	map<int, LL> miss(int x, int y) {
		map<int, LL> ret; int c[4];
		int d0 = 0; rep(i, 0, 3) if (Bomb[y][i] == Bomb[y][(i + 1) % 4]) ++d0;
		int mxc = *max_element(Bomb[x], Bomb[x] + 4);
		if (col < mxc) return ret;
		for (c[0] = 0; c[0] <= mxc; ++c[0])
			for (c[1] = 0; c[1] <= mxc; ++c[1])
				for (c[2] = 0; c[2] <= mxc; ++c[2])
					for (c[3] = 0; c[3] <= mxc; ++c[3]) {
						bool ok = 1; int s0 = 0, s1 = 0;
						rep(i, 0, 2) rep(j, i + 1, 3)
							if ((Bomb[y][i] == Bomb[y][j] && c[i] != c[j]) || (c[i] == c[j] && c[i] && Bomb[y][i] != Bomb[y][j]))
								{ok = 0; break;}
						if (!ok) continue;
						rep(i, 0, 3) s1 += Bomb[x][i] == c[i];
						rep(i, 0, 3) if (!c[i]) {
							bool ok = 1;
							rep(j, 0, i - 1) if (Bomb[y][j] == Bomb[y][i]) {ok = 0; break;}
							if (ok) ++s0;
						}
						(ret[d0 + s1] += Power[col - mxc][s0]) %= MOD;
					}
		return ret;
	}
	void eiyagaeshi(){
		A0.biu(0);
		rep(i, 0, 14) rep(j, 0, 14){
			auto T = miss(i, j);
			for (auto p0 : T){
				int d0 = p0.first; LL v0 = p0.second;
				rep(t, d0, k) A0[j * (k + 1) + t][i * (k + 1) + t - d0] = v0;
			}
		}
		rep(i, 0, n) A0[n][i] = 1;
	}
	void yoake(){
		v0.biu(0);
		rep(i, 0, 14){
			int mxc = *max_element(Bomb[i], Bomb[i] + 4);
			int s1 = 0; rep(j, 0, 3) s1 += (Bomb[i][j] == Bomb[i][(j + 1) % 4]);
			if (s1 > k) continue;
			v0[i * (k + 1) + s1][0] = Power[col][mxc];
		}
	}
	int find(int C, int K, long long H) {
		col = C; k = K; n = 15 * (K + 1);
		eiyagaeshi(); yoake();
		return (extend(A0, H) * v0)[n][0];
	}
};

