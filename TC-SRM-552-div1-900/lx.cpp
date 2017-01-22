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
const int N = 1e6 + 10;

bool vis[N];
int prime[N], tot;

//线性筛
void Linear_Shaker(int n) {
	rep (i, 2, n) {
		if (!vis[i]) {
			prime[++tot] = i;
		}
		rep (j, 1, tot) {
			int to = prime[j] * i;
			if (to > n)  break ;
			vis[to] = 1;
			if (i % prime[j] == 0)  break ;
		}
	}
}

class HolyNumbers {
private :
	//令calc(v, step) 表示 [step, tot] 中的质数拼出的<=v的圣光数字个数
	LL calc(LL v, int step) {
		if (step > tot || v < prime[step]) {
			return 1;
		}
		if (v < (LL)prime[step] * prime[step]) {		//剪枝：若 v < p[step]^2，则<=v的圣光数字中至多含一个质因子
			int k = upper_bound(prime + step, prime + tot + 1, v) - prime;
			return k - step + 1;
		}
		LL res = calc(v, step + 1);
		v /= prime[step];
		LL p2 = (LL) prime[step] * prime[step];
		while (v) {
			res += calc(v, step + 1);
			v /= p2;
		}
		return res;
	}
public :
	//搜索，数学
	LL count(LL Lim, LL mP) {
		Linear_Shaker(mP);
		return calc(Lim, 1);
	}
};
