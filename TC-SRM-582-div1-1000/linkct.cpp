#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 500005;
const double eps = 1e-3;

class SemiPerfectPower{
public:
	bool P2[MAXN], P3[MAXN], isComp[MAXN];
	int prime[MAXN], pcnt, mu[MAXN], low[MAXN], pdiv[105];
	vector <int> cnt[MAXN];
	LL get2root(LL x){
		LL l = 0, r = 1000000000, mid;
		while(l < r){
			mid = (l + r + 1) >> 1;
			if(mid * mid <= x) l = mid;
			else r = mid - 1;
		} return r;
	}
	LL get3root(LL x){
		LL l = 0, r = 1000000, mid;
		while(l < r){
			mid = (l + r + 1) >> 1;
			if(mid * mid * mid <= x) l = mid;
			else r = mid - 1;
		} return r;
	}
	LL get4root(LL x){
		LL l = 0, r = 20000, mid;
		while(l < r){
			mid = (l + r + 1) >> 1;
			if(mid * mid * mid * mid <= x) l = mid;
			else r = mid - 1;
		} return r;
	}
	void preprocess(LL n){
		int i, j, L, I, L_;
		memset(P2, false, sizeof(P2));
		memset(P3, false, sizeof(P3));
		memset(isComp, false, sizeof(isComp));
		L = get3root(n);
		mu[1] = low[1] = 1;
		for(i = 2, pcnt = 0; i <= L; ++ i){
			if(!isComp[i]){
				mu[prime[++ pcnt] = i] = -1;
				low[i] = i;
				if(i <= L / i){
					for(j = I = i * i; j <= L; j += I)
						P2[j] = true;
					if(i <= L / i / i)
						for(j = I = i * i * i; j <= L; j += I)
							P3[j] = true;
				}
			}
			for(j = 1; i * prime[j] <= L; ++ j){
				isComp[i * prime[j]] = true;
				low[i * prime[j]] = prime[j];
				if(i % prime[j] == 0){
					mu[i * prime[j]] = 0;
					break;
				} mu[i * prime[j]] = -mu[i];
			}
		} L_ = get4root(n);
		for(i = 1; i <= L_; ++ i){
			cnt[i].push_back(0);
			for(j = i; j <= L; j += i){
				cnt[i].push_back(cnt[i].back());
				if(!P2[j]) ++ cnt[i].back();
			}
		}
	}
	int gcd(int a, int b){return b ? gcd(b, a % b) : a;}
	LL calc(LL n){
		int i, j, k, L, L_, L__, bmax, g, a_, k_, t1, t2, N, now, c;
		LL ans = 0LL; L = get3root(n);
		for(i = 1; i <= L; ++ i){
			if(P2[i]) continue;
			ans += get2root(n / i) - i;
		}
		L_ = get4root(n);
		for(i = 1; i <= L_; ++ i){
			if(P3[i]) continue;
			L__ = get3root(i);
			bmax = get3root(n / i);
			for(j = 1; j <= L__; ++ j){
				g = gcd(i, j * j), a_ = i / g, k_ = j * j / g;
				if(P2[a_]) continue;
				for(c = 0, now = a_; now != 1; )
					for(pdiv[++ c] = low[now], now /= low[now]; low[now] == pdiv[c]; now /= low[now]) ;
				for(k = 0, N = 1 << c; k < N; ++ k){
					for(t1 = 0, t2 = 1; t1 < c; ++ t1)
						if(k & (1 << t1)) t2 *= pdiv[t1 + 1];
					ans += mu[t2] * (cnt[t2][bmax / k_ / t2] - cnt[t2][i / k_ / t2]);
				}
			}
		} return ans;
	}
	LL count(LL l, LL r){
		preprocess(r);
		return calc(r) - calc(l - 1);
	}
};
