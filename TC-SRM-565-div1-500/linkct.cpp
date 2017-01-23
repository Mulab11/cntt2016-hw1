#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int SQRT = 100005;

class TheDivisionGame{
public:
	vector <int> cur, sg; LL ans;
	int prime[SQRT], pcnt, cnt[35]; bool isComp[SQRT];
	LL countWinningIntervals(int l, int r){
		int plimit = int(sqrt(r * 1.0) + 1e-5), i, j;
		for(i = l; i <= r; ++ i){
			cur.push_back(i);
			sg.push_back(0);
		} memset(isComp, false, sizeof(isComp));
		for(i = 2; i <= plimit; ++ i){ //Linear sieve for prime under sqrt(r)
			if(!isComp[i]){
				prime[++ pcnt] = i;
				for(j = ((l - 1) / i + 1) * i; j <= r; j += i) //Using all prime under sqrt(r) to factorize [l, r]; complexity L log L + sqrt log log sqrt(Eratothenes sieve)
					while(cur[j - l] % i == 0)
						cur[j - l] /= i, ++ sg[j - l];
			}
			for(j = 1; i * prime[j] <= plimit; ++ j){
				isComp[i * prime[j]] = true;
				if(i % prime[j] == 0) break;
			}
		}
		for(i = l; i <= r; ++ i)
			if(cur[i - l] != 1) ++ sg[i - l];
		memset(cnt, 0, sizeof(cnt));
		cnt[0] = 1;
		for(i = l, j = ans = 0; i <= r; ++ i){
			ans += cnt[j ^= sg[i - l]];
			++ cnt[j];
		} return LL(r - l) * (r - l + 1) / 2 - ans;
	}
};
