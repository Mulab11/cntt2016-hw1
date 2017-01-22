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

class XorCards {
private :
	LL bin[65];
	LL base[65];

	bool insert(LL v) {
		if (!v) return 0;
		down (i, 63, 0) {
			if (v & bin[i]) {
				if (!base[i]) {
					base[i] = v;
					return 1;
				} else {
					v ^= base[i];
					if (!v) return 0;
				}
			}
		}
		assert(0);
	}
public :
	LL numberOfWays(vector<LL> num, LL lim) {
		bin[0] = 1;
		rep (i, 1, 63) bin[i] = bin[i - 1] << 1;
		int free = 0;
		rep (i, 0, num.size()-1) {
			free += insert(num[i]) == 0;
		}
		rep (i, 0, 63) if (base[i]) {
			rep (j, i+1, 63) if (base[j] & bin[i]) {
				base[j] ^= base[i];
			}
		}
		LL ans = 0, now = 0;
		down (i, 63, 0) {
			if ((lim & bin[i])) {
				if (!(now & bin[i]) || base[i]) {
					int cnt = 0;
					down (j, i-1, 0) {
						cnt += (base[j] > 0);
					}
					ans += bin[cnt];
					now = max(now, now ^ base[i]);
					if (!(now & bin[i])) break ;
				}
			} else {
				if (now & bin[i]) {
					if (!base[i]) break ;
					now ^= base[i];
				}
			}
		}
		if (lim == now) ans++;
		ans <<= free;
		return ans;
	}
};
