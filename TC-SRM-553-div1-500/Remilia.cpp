#include<bits/stdc++.h>

#define REP(i, l, r) for(int i = (l); i <= (r); i++)

using namespace std;

const int MOD = 1e9+7,N = 55;

char a[N][N];
int f[N][N], can[N][N], ans, n, m;

struct TwoConvexShapes{
	void pp1(){
		//由上至下不降
		REP(i, 0, m) f[0][i] = 1;
		REP(i, 1, n) REP(j, 0, m){
			f[i][j] = j ? f[i][j - 1] : 0;
			if (can[i][j])
				f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
		}
		ans = (ans + f[n][m]) % MOD;
	}
	void pp2(){
		//由上至下不增
		REP(i, 1, n / 2) REP(j, 0, m) swap(can[i][j], can[n - i + 1][j]);
		pp1();
		REP(i, 1, n / 2) REP(j, 0, m) swap(can[i][j], can[n - i + 1][j]);
	}
	void pp3(){
		//每列数都一样
		REP(j, 0, n){
			int flag = 1;
			REP(i, 1, j) if (!can[i][m]) {flag = 0;break;}
			REP(i, j + 1, n) if (!can[i][0]) {flag = 0;break;}
			ans -= flag;
		}
	}
	void pp4(){
		//每行数都一样
		REP(j, 0, m){
			int flag = 1;
			REP(i, 1, n) flag &= can[i][j];
			ans -= flag;
		}
	}
	void pp5(){
		//所有格子颜色都相同
		REP(i, 1, n) REP(j, 1, m) if (a[i][j] == 'W') return;
		++ans;
	}
	void pp6(){
		REP(i, 1, n) REP(j, 0, m){
			can[i][j] = 1;
			REP(k, 1, j) if (a[i][k] == 'W') {can[i][j] = 0; break;}
			REP(k, j + 1, m) if (a[i][k] == 'B') {can[i][j] = 0; break;}
		}
		pp1();pp2();pp3();pp4();pp5();
	}
	int countWays(vector <string> grid){
		n = grid.size(), m = grid[0].size(), ans = 0;
		REP(i, 1, n) REP(j, 1, m) a[i][j] = grid[i - 1][j - 1];
		pp6();
		REP(i, 1, n) REP(j, 1, m)
			if (a[i][j] == 'B') a[i][j] = 'W'; else
			if (a[i][j] == 'W') a[i][j] = 'B';
		pp6();
		return (ans + MOD) % MOD;
	}
};