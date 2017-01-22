/*
	Easy dp.
	Easy comments.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class Stamp {
	public:
	LL dp(string st, int l){ //Easy dp
		int n = st.length(); st = ' ' + st;
		LL DP[64]; DP[0] = 0;
		for (int i = 1; i <= n; ++i){
			char c = st[i];
			DP[i] = 2333333333ll;
			for (int j = i - 1; j >= 0; --j){
				if (i - j >= l) DP[i] = min(DP[i], DP[j] + (i - j - 1) / l + 1); //DP[i]=min{DP[j]+floor((i-j)/l)}
				if (st[j] != c && c != '*' && st[j] != '*') break;
				if (st[j] != '*') c = st[j];
			}
		}
		return DP[n];
	}
	int getMinimumCost(string desiredColor, int stampCost, int pushCost) {
		LL ret = 2333333333333ll; int n = desiredColor.length();
		for (int len = 1; len <= n; ++len){ // Go over all the possible lengths
			LL t = dp(desiredColor, len) * pushCost + (LL)stampCost * len; // Calculate the cost
			if (t < ret) ret = t; //Update answer
		}
		return ret;
	}
};

/*
	hifumi hifumi hifumi hifumi hihifu
	hifumi hifumi hifumi hifumi hihifu
	hifumi hifumi hifumi hifumi hihifu
	hihihihi hihihihi hihihihi hihihihi hihihihi hihihihi hifumiyo hifumiyo
		- Marisa wa Taihen na Mono wo Nusunde Ikimashita
*/

