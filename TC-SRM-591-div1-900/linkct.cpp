#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000009;

class StringPath{
public:
	int n, m, f[1 << 9][1 << 9], g[1 << 9][1 << 9];
	inline void update(int &a, int b){if((a += b) >= MOD) a -= MOD;}
	inline int judge(int st, int pos){
		return ((st | (st << 1)) & (1 << pos)) ? 1 : 0;
	}
	inline int op(int st, int pos, bool sgn){
		if((sgn && (st & (1 << pos)) == 0) || (!sgn && (st & (1 << pos)))) st ^= 1 << pos;
		return st;
	}
	int countBoards(int r, int c, string a, string b){
		if(a[0] != b[0] || a[r + c - 2] != b[r + c - 2] || r == 1 || c == 1) return 0;
		memset(f, 0, sizeof(f));
		n = r, m = c; f[1][1] = 1;
		int i, j, k, s1, s2, M = 1 << (m + 1), cur, ans = 0, last, s1_, s2_;
		for(k = 1, last = 0; k < n + m - 1; ++ k)
			for(i = min(k, n - 1); i >= 0 && k - i < m; -- i){
				j = k - i; //Deciding (i, j)
				memset(g, 0, sizeof(g));
				for(s1 = 1; s1 < M; ++ s1)
					for(s2 = 1; s2 < M; ++ s2){
						if((cur = f[s1][s2]) == 0) continue;
						if(j == 0 || i == n - 1) s1_ = s1, s2_ = s2;
						else{
							s1_ = op(op(s1, last, s1 & (1 << m)), m, false);
							s2_ = op(op(s2, last, s2 & (1 << m)), m, false);
						}
						if(a[k] != b[k]){
							update(g[s1_ | (judge(s1, j) << m)][s2_], cur);
							update(g[s1_][s2_ | (judge(s2, j) << m)], cur);
							update(g[s1_][s2_], cur * 24LL % MOD);
						}else{
							update(g[s1_ | (judge(s1, j) << m)][s2_ | (judge(s2, j) << m)], cur);
							update(g[s1_][s2_], cur * 25LL % MOD);
						}
					}
				memset(f, 0, sizeof(f));
				for(s1 = 0; s1 < M; ++ s1)
					for(s2 = 0; s2 < M; ++ s2)
						if(i == 0 || j == m - 1){
							s1_ = op(op(s1, j, s1 & (1 << m)), m, false);
							s2_ = op(op(s2, j, s2 & (1 << m)), m, false);
							update(f[s1_][s2_], g[s1][s2]);
						}else update(f[s1][s2], g[s1][s2]);
				last = j;
			}
		for(s1 = 1; s1 < M; ++ s1)
			for(s2 = 1; s2 < M; ++ s2)
				if((s1 & (1 << (m - 1))) && (s2 & (1 << (m - 1))))
					update(ans, f[s1][s2]);
		return ans;
	}
};
