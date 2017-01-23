#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXST = 17, MAXMT = MAXST * 9;
const LL MOD = 1234567891LL;

class TheBrickTowerHardDivOne{
public:
	int st[MAXST][6], col[6], scnt, n, m, c, mp[5];
	LL tr[MAXMT][MAXMT], res[MAXMT][MAXMT], tmp[MAXMT][MAXMT];
	inline int calc(){ //Calculate the number of illegal positions
		int i, j, ret = 0;
		for(i = 0; i < 4; ++ i)
			for(j = 0; j < i; ++ j)
				if(col[i] == col[j] && (i ^ j) != 3)
					++ ret;
		return ret;
	}
	void mul(LL x[MAXMT][MAXMT], const LL y[MAXMT][MAXMT]){
		int i, j, k;
		for(i = 0; i <= n; ++ i)
			for(j = 0; j <= n; ++ j)
				for(tmp[i][j] = k = 0; k <= n; ++ k)
					(tmp[i][j] += x[i][k] * y[k][j]) %= MOD;
		memcpy(x, tmp, sizeof(tmp));
	}
	void dfsGetStat(int x, int mxc){
		if(mxc > c) return;
		if(x == 4){ //col[0..3] stores the colors of the 2*2 tiles; col[4] kinds of colors used; generates col[5] illegal positions on this level alone
			if((col[5] = calc()) > m) return;
			col[4] = mxc;
			memcpy(st[++ scnt], col, sizeof(col)); //st[] stores all the possible situations; scnt in total
			return;
		}
		for(int i = 1; i <= mxc + 1; ++ i)
			col[x] = i, dfsGetStat(x + 1, max(mxc, i));
	}
	LL A(LL n, int m){
		if(n < m) return 0LL;
		LL ret = 1LL; int i;
		for(i = 0; i < m; ++ i)
			(ret *= n - i) %= MOD;
		return ret;
	}
	void dfsGetMap(int dw, int up, int x){ //Enumerate all possible color mappings from up to dw
		if(x > st[up][4]){
			int i, ocnt = 0, dt = st[up][5];
			for(i = 1; i < x; ++ i)
				if(mp[i]) ++ ocnt;
			for(i = 0; i < 4; ++ i)
				if(mp[st[up][i]] == st[dw][i])
					++ dt;
			for(i = 0; i + dt <= m; ++ i)
				(tr[(i + dt) * scnt + up][i * scnt + dw] += A(c - st[dw][4], x - 1 - ocnt)) %= MOD;
			return;
		} int i, j;
		mp[x] = 0; dfsGetMap(dw, up, x + 1); //mp[x] = 0 denotes that color x in up is different from any color in dw
		for(i = 1; i <= st[dw][4]; ++ i){ //mp[x] > 0 denotes that color x in up is the same color as color mp[x] in dw
			for(j = 1; j < x; ++ j)
				if(i == mp[j]) break;
			if(j < x) continue; //Color already exists in mp[1..x-1]
			mp[x] = i, dfsGetMap(dw, up, x + 1);
		}
	}
	int find(int c_, int m_, LL h){
		int i, j; c = c_, m = m_;
		dfsGetStat(0, 0); //Generate all possible situations for a single level
		n = (m + 1) * scnt;
		for(i = 1; i <= scnt; ++ i){ //Construct the transition matrix; 1, 2, .., scnt denote situations with 0 illegal position, scnt+1, scnt+2, .., 2*scnt denote situations with 1 illegal position, and so on
			for(j = 1; j <= scnt; ++ j) //Enumerate all level pairs & relation between their colors
				dfsGetMap(i, j, 1);
			for(j = 0; j <= m; ++ j) //0 denotes the final answer
				tr[0][j * scnt + i] = 1;
		} tr[0][0] = 1;
		for(i = 0; i <= n; ++ i)
			res[i][i] = 1;
		while(h){ //Quick pow for matrix
			if(h & 1LL) mul(res, tr);
			mul(tr, tr); h >>= 1;
		} LL ans = 0;
		for(i = 1; i <= scnt; ++ i)
			(ans += A(c, st[i][4]) * res[0][st[i][5] * scnt + i]) %= MOD;
		return ans;
	}
};
