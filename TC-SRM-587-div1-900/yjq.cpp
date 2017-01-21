#include <bits/stdc++.h>


using namespace std;


int n, m ; 

const int MAXN = 10010 ; 

struct Edge {
		int l, r, c, nxt; 
} e[MAXN << 1] ;

bool flag = 1 ;  

int ecnt = 0, hed[MAXN] ; 

void addedge(int l, int r, int c) { 
		++ecnt, e[ecnt].l = l, e[ecnt].r = r, e[ecnt].c = c, e[ecnt].nxt = hed[l], hed[l] = ecnt ; 
}

int col[MAXN] ; 

class ThreeColorability {
		public:
				void Dfs(int x) {
						for (int i = hed[x]; i; i = e[i].nxt) { 
								if (col[e[i].r] < 0) col[e[i].r] = col[x] ^ e[i].c, Dfs(e[i].r) ;   

								else if (col[e[i].r] != (col[x] ^ (e[i].c))) flag = 0;  
						}
				}
				vector<string> lexSmallest(vector<string> mp) {
						n = mp.size(), m = mp[0].size();
						for(int i = 0; i < n; i ++) {
								for(int j = 0; j < m; j ++) {
										if(mp[i][j] != '?') addedge(i + m, j, mp[i][j] == 'Z');
								}
						}
						memset(col, -1, sizeof col) ; 
						col[m] = 0;
						Dfs(m) ; 
						for(int i = 0; i < m; i++) {
								if(col[i] < 0) col[i] = 0, Dfs(i);
						}
						for(int i = m + 1; i < n + m; i++) {
								if(col[i] < 0) col[i] = col[0], Dfs(i);
						}
						if(!flag) return vector<string>();
						for(int i = 0; i < n; i++) {
								for(int j = 0; j < m; j++) mp[i][j] = col[i + m] ^ col[j] ? 'Z' : 'N';
						}
						return mp;
				}
};
