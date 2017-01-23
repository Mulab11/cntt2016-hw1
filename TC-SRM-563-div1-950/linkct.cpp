#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int dx[5] = {-1, 0, 0, 0, 1}, dy[5] = {0, -1, 0, 1, 0};
const int MOD = 1000000009, MAXN = 45;

class CoinsGame{
public:
	struct newTag{
		int d[5], id;
		bool operator < (const newTag &rhs) const{
			for(int i = 0; i < 5; ++ i)
				if(d[i] != rhs.d[i]) return d[i] < rhs.d[i];
			return id < rhs.id;
		}
		bool operator != (const newTag &rhs) const{
			for(int i = 0; i < 5; ++ i)
				if(d[i] != rhs.d[i]) return true;
			return false;
		}
	}St[MAXN * MAXN];
	int n, m, r, c, tag[MAXN * MAXN], id[MAXN][MAXN], nt[MAXN * MAXN], pos[MAXN * MAXN][2];
	inline bool inmap(int x, int y){return x >= 0 && x < r && y >= 0 && y < c;}
	inline bool same(){
		for(int i = 1; i <= n; ++ i)
			if(tag[i] != nt[i]){
				memcpy(tag, nt, sizeof(nt));
				return false;
			}
		return true;
	}
	int ways(vector <string> g){
		int i, j, x, y; LL ans = 0LL;
		r = g.size(), c = g[0].length();
		memset(tag, 0, sizeof(tag));
		memset(id, 0, sizeof(id));
		for(i = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j)
				if(g[i][j] != '#'){
					tag[id[i][j] = ++ n] = 1;
					pos[n][0] = i, pos[n][1] = j;
				}
		if(n <= 1) return 0;
		do{
			for(i = 1; i <= n; ++ i){
				for(j = 0; j < 5; ++ j){
					x = pos[i][0] + dx[j];
					y = pos[i][1] + dy[j];
					if(inmap(x, y)){
						if(g[x][y] == '#') St[i].d[j] = tag[i];
						else St[i].d[j] = tag[id[x][y]];
					}else St[i].d[j] = 0;
				} St[i].id = i;
			} sort(St + 1, St + 1 + n);
			for(i = 1, m = 0; i <= n; ++ i)
				if(i == 1 || St[i] != St[i - 1])
					nt[St[i].id] = ++ m;
				else nt[St[i].id] = m;
		}while(!same()); //Try to divide non-equivalent coins
		sort(tag + 1, tag + 1 + n);
		for(i = j = 2; i <= n; ++ i)
			if(tag[i] == tag[i - 1]){
				if((j <<= 1) >= MOD)
					j -= MOD;
			}else (ans += j - 1) %= MOD, j = 2;
		(ans += j - 1) %= MOD;
		for(i = j = 1; i <= n; ++ i)
			if((j <<= 1) >= MOD) j -= MOD;
		return (j - ans - 1 + MOD) % MOD;
	}
};
