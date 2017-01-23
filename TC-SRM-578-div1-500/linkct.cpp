#include <bits/stdc++.h>
using namespace std;
const int MAXN = 305, MAXM = 305, MOD = 1000000007;

class WolfInZooDivOne{
public:
	struct Wolves{
		int l, r;
		bool operator < (const Wolves &rhs) const{
			return l == rhs.l ? r > rhs.r : l < rhs.l;
		}
	}wolf[MAXM], wolf_[MAXM];
	int dp[MAXN][MAXN], m, m_;
	int count(int n, vector <string> llist, vector <string> rlist){
		int i, j, rht, k, ans = 0; stringstream readin;
		for(i = 0; i < int(llist.size()); ++ i) readin << llist[i];
		for(m_ = 0; readin >> wolf_[0].l; wolf_[++ m_].l = wolf_[0].l) ;
		for(i = 0; i < int(rlist.size()); ++ i) readin << rlist[i];
		for(m_ = 0; readin >> wolf_[0].r; wolf_[++ m_].r = wolf_[0].r) ;
		sort(wolf_ + 1, wolf_ + 1 + m_);
		for(i = 1, m = 0, rht = -1; i <= m_; ++ i)
			if(wolf_[i].r > rht){
				wolf[++ m] = wolf_[i];
				rht = wolf_[i].r;
			}
		wolf[m + 1].l = wolf[m + 1].r = n + 1;
		dp[0][0] = ans = 1;
		for(i = k = 1; i <= n; ++ i){
			while(wolf[k].r < i) ++ k;
			dp[i][0] = 1;
			for(j = 1; j < i; ++ j)
				dp[i][j] = (1 + dp[i][j - 1] + dp[j][min(j, wolf[k].l) - 1]) % MOD;
			(ans += dp[i][i - 1]) %= MOD;
		} return ans;
	}
};
