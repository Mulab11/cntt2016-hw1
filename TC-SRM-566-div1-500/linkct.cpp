#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 355;
const LL MOD = 1000000007LL;

class PenguinEmperor{
public:
	LL tr[MAXN][MAXN], tmp[MAXN], ans[MAXN], base[MAXN];
	int countJourneys(int n, LL T){
		int i, j;
		memset(tr, 0, sizeof(tr));
		tr[0][0] = 1;
		for(i = 1; i <= n; ++ i)
			for(j = 0; j < n; ++ j){
				if((tr[i][j] = tr[i - 1][(j - i + n) % n] + tr[i - 1][(j + i) % n]) >= MOD)
					tr[i][j] -= MOD;
				if((j - i + n) % n == (i + j) % n && (tr[i][j] -= tr[i - 1][(i + j) % n]) < 0LL) //Transfer from the same city is considered identical
					tr[i][j] += MOD;
			}
		if(T <= n) return tr[T][0];
		memcpy(ans, tr[T % n], sizeof(ans));
		memcpy(base, tr[n], sizeof(base));
		for(T /= n; T; T >>= 1){
			if(T & 1){
				memset(tmp, 0, sizeof(tmp));
				for(i = 0; i < n; ++ i)
					for(j = 0; j < n; ++ j)
						tmp[(i + j) % n] = (tmp[(i + j) % n] + ans[i] * base[j]) % MOD;
				memcpy(ans, tmp, sizeof(ans));
			}
			memset(tmp, 0, sizeof(tmp));
			for(i = 0; i < n; ++ i)
				for(j = 0; j < n; ++ j)
					tmp[(i + j) % n] = (tmp[(i + j) % n] + base[i] * base[j]) % MOD;
			memcpy(base, tmp, sizeof(base));
		} return ans[0];
	}
};
