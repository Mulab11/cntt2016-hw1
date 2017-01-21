#include <bits/stdc++.h>

using namespace std;

int n, m;

const int MAXN = 60 ; 

int fa[MAXN * MAXN];

int findfa(int x) {return fa[x] == x ? x : fa[x] = findfa(fa[x]);} 

int id(int x, int y) {return x * m + y; }

class ArcadeManao {
		public:
				int shortestLadder(vector<string> level, int x, int y) {
						n = level.size(), m = level[0].size() ;
						x = x - 1, y = y - 1 ; 
						for (int i = 0; i < n * m; i ++) fa[i] = i ; 
						for(int i = 0; i < n; i ++) {
								for(int j = 1; j < m; j ++) {
										if(level[i][j] == 'X' && level[i][j - 1] == 'X') fa[findfa(id(i, j))] = findfa(id(i, j -1)) ; 
								}
						}
						for(int l = 1; l <= n; l ++)  {
								if (findfa(id(x, y)) == findfa(id(n - 1, 0))) return l - 1;  
								for(int i = 0; i + l < n; i ++) {
										for(int j = 0; j < m; j ++) {
												if(level[i][j] == 'X' && level[i + l][j] == 'X') fa[findfa(id(i, j))] = findfa(id(i + l, j)) ; 
										}
								}
						}
						return -1;
				}
};
