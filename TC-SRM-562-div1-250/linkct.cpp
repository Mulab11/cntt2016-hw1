#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class PastingPaintingDivOne{
public:
	int board[MAXN * 3][MAXN * 3], n, m, c;
	vector <LL> cnt[MAXN * 2], ans;
	inline int get(char x){return x == 'R' ? 0 : (x == 'G' ? 1 : 2);}
	vector <LL> countColors(vector <string> g, int T){
		int i, j, k;
		n = g.size(), m = g[0].length(), c = min(n, m);
		cnt[0].resize(3);
		memset(board, -1, sizeof(board));
		for(i = 1; i <= 2 * c; ++ i){ //Simulate the first 2c steps in O(nm min(n,m))
			cnt[i] = cnt[i - 1];
			for(j = 0; j < n; ++ j)
				for(k = 0; k < m; ++ k){
					if(g[j][k] == '.') continue;
					if(board[i + j][i + k] != -1)
						-- cnt[i][board[i + j][i + k]];
					++ cnt[i][board[i + j][i + k] = get(g[j][k])];
				}
		} if(T <= 2 * c) return cnt[T];
		for(i = 1; i <= c; ++ i)
			for(j = 0; j < 3; ++ j)
				cnt[c + i][j] -= cnt[c][j];
		ans = cnt[c], T -= c;
		for(i = 0; i < 3; ++ i){
			ans[i] += (T / c) * cnt[c * 2][i];
			if(T % c) ans[i] += cnt[c + (T % c)][i];
		} return ans;
	}
};
