#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;

class ThreeColorability{
public:
	int d[55][55], n, m, d_[55][55]; queue <pii> q;
	inline bool expand(int i, int j){
		int c = 0, s = 0, x, y;
		if(d[0][0] == -1) x = 0, y = 0, ++ c;
		else s ^= d[0][0];
		if(d[i][j] == -1) x = i, y = j, ++ c;
		else s ^= d[i][j];
		if(d[i][0] == -1) x = i, y = 0, ++ c;
		else s ^= d[i][0];
		if(d[0][j] == -1) x = 0, y = j, ++ c;
		else s ^= d[0][j];
		if(c == 0 && d[0][0] != (d[i][j] ^ d[i][0] ^ d[0][j])) return false;
		else if(c == 1) d[x][y] = s, q.push(pii(x, y));
		return true;
	}
	bool bfs(){
		int i, j; pii now;
		while(!q.empty()){
			now = q.front(); q.pop();
			if(now.fi == 0 && now.se == 0){
				for(i = 1; i < n; ++ i)
					for(j = 1; j < m; ++ j)
						if(!expand(i, j)) return false;
			}else if(now.fi == 0){
				for(i = 1, j = now.se; i < n; ++ i)
					if(!expand(i, now.se)) return false;
			}else if(now.se == 0){
				for(j = 1, i = now.fi; j < m; ++ j)
					if(!expand(now.fi, j)) return false;
			}else if(!expand(now.fi, now.se)) return false;
		} return true;
	}
	vector <string> lexSmallest(vector <string> g){
		int i, j; vector <string> emp;
		n = g.size(), m = g[0].length();
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				if(g[i][j] == 'Z') d[i][j] = 1;
				else if(g[i][j] == 'N') d[i][j] = 0;
				else d[i][j] = -1;
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				if(~d[i][j])
					q.push(pii(i, j));
		if(!bfs()) return emp;
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				if(~d[i][j]) continue;
				memcpy(d_, d, sizeof(d));
				d[i][j] = 0; q.push(pii(i, j));
				if(!bfs()){
					memcpy(d, d_, sizeof(d));
					d[i][j] = 1; q.push(pii(i, j));
					if(!bfs()) return emp;
				}
			}
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				if(g[i][j] == '?')
					g[i][j] = d[i][j] ? 'Z' : 'N';
		return g;
	}
};
