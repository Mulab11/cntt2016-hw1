/*
	Brute force. (with some optimization)
	No comment.
*/ 

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 1 << 20;

bool bad[MAXN];
LL prime[MAXN], nP;
void getPrimes(int maximalPrime){
	nP = 0;
	for (int i = 2; i <= maximalPrime; ++i)
		if (!bad[i]){
			prime[++nP] = i;
			for (int j = i + i; j <= maximalPrime; j += i)
				bad[j] = 1;
		}
}
LL F(LL upTo, int x){
	if (x > nP || prime[x] > upTo) return 1;
	if (prime[x] * prime[x] > upTo) return upper_bound(prime + x, prime + nP + 1, upTo) - prime - x + 1;
	LL ret = F(upTo, x + 1);
	for (LL u = upTo / prime[x]; u > 0; u /= ((LL)prime[x] * prime[x]))
		ret += F(u, x + 1);
	return ret;
}
class HolyNumbers {
	public:
	long long count(long long upTo, int maximalPrime) {
		getPrimes(maximalPrime); return F(upTo, 1);
	}
};

/*
	'Big force makes miracle.'
		- idiom
*/
