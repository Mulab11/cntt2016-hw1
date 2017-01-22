/*
	Simple dp.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class CuttingBitString {
	public:
	int getmin(string S) {
		int n = S.length();
		S = ' ' + S;
		static int dp[233];
		set<LL> ok;
		for (LL s = 1; s <= (1ll << 50); s *= 5) ok.insert(s);
		for (int i = 1; i <= n; ++i){
			dp[i] = 23333;
			LL sum = 0;
			for (int j = i; j >= 1; --j) if (S[j] & 1){
				sum |= 1ll << (i - j);
				if (ok.count(sum) && dp[j - 1] + 1 < dp[i])
					dp[i] = dp[j - 1] + 1;
			}
		}
		return dp[n] == 23333 ? -1 : dp[n];
	}
};

/*
	O-oooooooooo AAAAE-A-A-I-A-U- JO-oooooooooooo AAE-O-A-A-U-U-A- E-eee-ee-eee AAAAE-A-E-I-E-A- JO-ooo-oo-oo-oo EEEEO-A-AAA-AAAA
		- Brain Power 
*/

