#include <bits/stdc++.h>
using namespace std;
const int dx[5] = {-1, 0, 0, 1, 0}, dy[5] = {0, -1, 1, 0, 0}, MAXN = 15;

class YetAnotherBoardGame{
public:
	int n, m, cur[MAXN][MAXN], st[MAXN][MAXN], ret;
	inline void operate(int x, int y, bool type){
		++ ret;
		for(int i = 0; i < 4 + type; ++ i)
			cur[x + dx[i]][y + dy[i]] ^= 1;
	}
	int solve(int type, int active){
		int i, j, tp; ret = 0;
		memcpy(cur, st, sizeof(st));
		for(i = 0; i < m; ++ i)
			if(active & (1 << i))
				operate(1, i + 1, type & (1 << i));
		for(i = 2; i <= n; ++ i)
			for(j = 0, tp = -1; j < m; ++ j)
				if(cur[i - 1][j + 1]){
					if(type & (1 << j)){
						if(tp == 0) return 1e9;
						operate(i, j + 1, true);
						tp = 1;
					}else{
						if(tp == 1) return 1e9;
						operate(i, j + 1, false);
						tp = 0;
					}
				}
		for(i = 1; i <= m; ++ i)
			if(cur[n][i]) return 1e9;
		return ret;
	}
	int minimumMoves(vector <string> board){
		int i, j, ans = 1e9, M;
		n = board.size(), m = board[0].length();
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				st[i + 1][j + 1] = int(board[i][j] == 'W');
		for(i = 0, M = 1 << m; i < M; ++ i){
			for(j = i; j; j = (j - 1) & i)
				ans = min(ans, min(solve(i, j), solve((M - 1) ^ i, j)));
			ans = min(ans, solve(i, 0));
		} return ans <= n * m ? ans : -1;
	}
};
