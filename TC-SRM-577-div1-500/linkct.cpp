#include <bits/stdc++.h>
using namespace std;
const int MN = 17, INF = 1e9;

class EllysChessboard{
public:
	int mxx[MN][MN], mxy[MN][MN], mnx[MN][MN], mny[MN][MN];
	int dp[MN][MN][MN][MN]; bool g[MN][MN];
	inline void shrink(int u, int d, int l, int r, int &u_, int &d_, int &l_, int &r_){
		u_ = mnx[u][l], l_ = mny[u][l];
		d_ = mxx[d][r], r_ = mxy[d][r];
	}
	int solve(int u, int d, int l, int r){
		if(u > d || l > r) return 0;
		int &cur = dp[u][d][l][r];
		if(~cur) return cur;
		cur = INF;
		int i, u_, d_, l_, r_, sum, t1, t2;
		if(u < d){
			shrink(u + 1, d, l, r, u_, d_, l_, r_);
			for(i = l, sum = 0, t1 = l_, t2 = r_; i <= r; ++ i)
				if(g[u][i]){
					sum += max(d - u, max(abs(t1 - i), abs(t2 - i)));
					t1 = min(t1, i), t2 = max(t2, i);
				}
			cur = min(cur, solve(u_, d_, l_, r_) + sum);
			shrink(u, d - 1, l, r, u_, d_, l_, r_);
			for(i = l, sum = 0, t1 = l_, t2 = r_; i <= r; ++ i)
				if(g[d][i]){
					sum += max(d - u, max(abs(t1 - i), abs(t2 - i)));
					t1 = min(t1, i), t2 = max(t2, i);
				}
			cur = min(cur, solve(u_, d_, l_, r_) + sum);
		}
		if(l < r){
			shrink(u, d, l + 1, r, u_, d_, l_, r_);
			for(i = u, sum = 0, t1 = u_, t2 = d_; i <= d; ++ i)
				if(g[i][l]){
					sum += max(r - l, max(abs(t1 - i), abs(t2 - i)));
					t1 = min(t1, i), t2 = max(t2, i);
				}
			cur = min(cur, solve(u_, d_, l_, r_) + sum);
			shrink(u, d, l, r - 1, u_, d_, l_, r_);
			for(i = u, sum = 0, t1 = u_, t2 = d_; i <= d; ++ i)
				if(g[i][r]){
					sum += max(r - l, max(abs(t1 - i), abs(t2 - i)));
					t1 = min(t1, i), t2 = max(t2, i);
				}
			cur = min(cur, solve(u_, d_, l_, r_) + sum);
		} return cur;
	}
	int minCost(vector <string> board){
		int i, j, k;
		for(i = 0; i < 8; ++ i)
			for(j = 0; j < 8; ++ j)
				if(board[i][j] == '#')
					g[i + j + 1][i - j + 8] = true;
		memset(dp, -1, sizeof(dp));
		for(i = 1; i < 16; ++ i)
			for(j = 1; j < 16; ++ j)
				dp[i][i][j][j] = 0;
		for(i = 0; i <= 16; ++ i){
			mxx[0][i] = 0;
			mxy[i][0] = 0;
		}
		for(i = 1; i < 16; ++ i)
			for(j = 1; j < 16; ++ j){
				for(k = 0; k <= j; ++ k)
					if(g[i][k]) break;
				if(k <= j) mxx[i][j] = i;
				else mxx[i][j] = mxx[i - 1][j];
				for(k = 0; k <= i; ++ k)
					if(g[k][j]) break;
				if(k <= i) mxy[i][j] = j;
				else mxy[i][j] = mxy[i][j - 1];
			}
		for(i = 0; i <= 16; ++ i){
			mnx[16][i] = 16;
			mny[i][16] = 16;
		}
		for(i = 15; i; -- i)
			for(j = 15; j; -- j){
				for(k = j; k < 16; ++ k)
					if(g[i][k]) break;
				if(k < 16) mnx[i][j] = i;
				else mnx[i][j] = mnx[i + 1][j];
				for(k = i; k < 16; ++ k)
					if(g[k][j]) break;
				if(k < 16) mny[i][j] = j;
				else mny[i][j] = mny[i][j + 1];
			}
		return solve(mnx[1][1], mxx[15][15], mny[1][1], mxy[15][15]);
	}
};
