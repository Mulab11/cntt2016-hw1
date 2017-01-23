#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int P[9] = {2, 3, 2, 5, 3, 7, 2, 3, 5}, C[9] = {1, 1, 2, 1, 1, 1, 3, 2, 1}, MAXK = 17;
const LL MOD = 1000000009LL;

class MegaFactorial{
public:
	LL tr[MAXK][MAXK], acc[MAXK][MAXK], res[MAXK][MAXK], cur[MAXK][MAXK]; int m;
	LL tmp[MAXK][MAXK], ans[MAXK], temp[MAXK], base[MAXK][MAXK], Res[35][MAXK][MAXK];
	void multiply(const LL x[MAXK][MAXK], const LL y[MAXK][MAXK], LL ret[MAXK][MAXK], LL mod){
		int i, j, k;
		memset(tmp, 0, sizeof(tmp));
		for(i = 0; i <= m; ++ i)
			for(j = 0; j <= m; ++ j)
				for(k = 0; k <= m; ++ k)
					tmp[i][j] = (tmp[i][j] + x[i][k] * y[k][j]) % mod;
		memcpy(ret, tmp, sizeof(tmp));
	}
	void quickPow(const LL x[MAXK][MAXK], int expo, LL mod){
		memset(res, 0, sizeof(res));
		memcpy(base, x, sizeof(base));
		for(int i = 0; i <= m; ++ i) res[i][i] = 1;
		while(expo){
			if(expo & 1) multiply(res, base, res, mod);
			multiply(base, base, base, mod);
			expo >>= 1;
		}
	}
	void update(const LL x[MAXK][MAXK], LL y[MAXK], LL mod){
		int i, j;
		memset(temp, 0, sizeof(temp));
		for(i = 0; i <= m; ++ i)
			for(j = 0; j <= m; ++ j)
				temp[i] = (temp[i] + x[i][j] * y[j]) % mod;
		memcpy(y, temp, sizeof(temp));
	}
	LL solve(int n, int p, LL mod){
		LL i; int j, k, c;
		memset(ans, 0, sizeof(ans)); ans[m] = 1;
		memset(tr, 0, sizeof(tr));
		memset(acc, 0, sizeof(acc));
		for(i = 0; i <= m; ++ i) tr[i][i] = acc[i][i] = 1;
		for(i = 1LL, c = 0; i <= n; i *= p, ++ c){
			memset(cur, 0, sizeof(cur));
			for(j = 0; j < m; ++ j){ //Construct new transition matrix for i
				for(k = j; k < m; ++ k)
					cur[j][k] = 1;
				cur[j][m] = c;
			} cur[m][m] = 1;
			multiply(cur, acc, tr, mod); //tr: 1, 2, ..., i
			quickPow(tr, (n % (i * p)) / i, mod); //res: 1, 2, .., i, i+1(=1), i+2(=2), .., (n%(i*p))/i * i
			n = n / (i * p) * (i * p);
			memcpy(Res[c], res, sizeof(res));
			quickPow(tr, p - 1, mod);
			multiply(acc, res, acc, mod); //acc: 1, 2, ..., i*p-1
		}
		for(i = c; i; -- i) //Reverse order
			update(Res[i - 1], ans, mod);
		return ans[0];
	}
	int countTrailingZeros(int n, int m_, int b){
		m = m_;
		return solve(n, P[b - 2], C[b - 2] * MOD) / C[b - 2];
	}
};
