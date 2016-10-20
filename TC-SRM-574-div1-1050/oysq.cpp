#line 2 "Tunnels.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int INF = 1e9;

class Tunnels {  
public:
	std::vector<std::string> g;
	int n, m, col[N + 9][N + 9], tot, up[N + 9], down[N + 9], deg[N + 9][N + 9], num[N * N + 9];

	bool valid(int x, int y) {
		return x >= 0 && x < n && y >= 0 && y < m && g[x][y] == 'X' && !col[x][y];
	}
	
	void dfs(int x, int y, int c) {
		//col denotes the id of component, num denotes the total squares in the component
		col[x][y] = c, num[c]++;
		//up, down represent the upper and lower limit of a component
		chkmin(up[c], x), chkmax(down[c], x);
		for(int i = 0; i < 4; ++i) {
			int tx = x + dir[i][0], ty = y + dir[i][1];
			if(valid(tx, ty)) dfs(tx, ty, c), ++deg[x][y], ++deg[tx][ty];//mark all squares' degree
		}
	}

	int dp(bool *lu, bool *ld, bool *ru, bool *rd, bool *lr) {
		int f[N + 9][N + 9][N + 9];

		//initialization
		for(int k = 0; k <= n; ++k)
			for(int i = 0; i <= n; ++i)
				for(int j = 0; j <= n; ++j)
					f[k][i][j] = -INF;
		
		f[n][0][0] = 0;
		for(int i = n - 1; i >= 0; --i)
			for(int a = 0; a <= n; ++a)
				for(int b = 0; b <= n; ++b)
					if(f[i + 1][a][b] > -INF) {
						for(int x = -1; x <= 1; ++x)
							for(int y = -1; y <= 1; ++y)
								if(a + x >= 0 && b + y >= 0) {
									bool flag = true;

									// check if valid
									if(lr[i]) {
										if(!i) flag &= (!x && !y) || (!x && y == -1) || (x == -1 && !y);
										else flag &= x != y && (x == 1 || y == 1);
									}
									else {
										if(lu[i]) flag &= x == 1;
										else if(ld[i]) flag &= x != 1;
										else flag &= x == 0;
										if(ru[i]) flag &= y == 1;
										else if(rd[i]) flag &= y != 1;
										else flag &= y == 0;
									}
									
									if(flag) {
										int add = (x == -1) + (y == -1);
										chkmax(f[i][a + x][b + y], f[i + 1][a][b] + add);
									}
								}
					}

		//calculate the answer
		int ans = 0;
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				chkmax(ans, f[0][i][j]);
		return ans;
	}
	
	int minimumTunnels(vector <string> _g) {
		static bool lu[N + 9], ru[N + 9], ld[N + 9], rd[N + 9], lr[N + 9];
		g = _g, n = SZ(g), m = SZ(g[0]);

		// dfs all components, mark related info
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(g[i][j] == 'X' && !col[i][j]) {
					++tot;
					up[tot] = n, down[tot] = 0;
					dfs(i, j, tot);
				}

		//check lu, ld, ru, rd, lr
		for(int i = 0; i < n; ++i) {
			if(g[i][0] == 'X') {
				int c = col[i][0];
				if(i && up[c] == i && ((deg[i][0] & 1) || !deg[i][0])) lu[i] = true;
				if(!lu[i] && down[c] == i && ((deg[i][0] & 1) || !deg[i][0])) ld[i] = true;
			}
			if(g[i][m - 1] == 'X') {
				int c = col[i][m - 1];
				if(i && up[c] == i && ((deg[i][m - 1] & 1) || !deg[i][m - 1])) ru[i] = true;
				if(!ru[i] && down[c] == i && ((deg[i][m - 1] & 1) || !deg[i][m - 1])) rd[i] = true;
			}
			if(g[i][0] == 'X' && g[i][m - 1] == 'X' && col[i][0] == col[i][m - 1]) {
 				int c = col[i][0];
				if(up[c] == down[c]) lr[i] = true;
			}
			if(lr[i]) lu[i] = ld[i] = ru[i] = rd[i] = false;
		}

		// ..   ..
		// X.   .X
		// X. & .X
		// ..   ..
		for(int i = 0; i < n - 1; ++i) {
			if(g[i][0] == 'X' && g[i + 1][0] == 'X' && lu[i] && ld[i + 1]) {
				if(i == 0) lu[i] = false;
				else ld[i + 1] = false;
			}
			if(g[i][m - 1] == 'X' && g[i + 1][m - 1] == 'X' && ru[i] && rd[i + 1]) {
				if(i == 0) ru[i] = false;
				else rd[i + 1] = false;
			}
		}

		// ....
		// XXXX
		// XXXX
		// XXXX
		// ....
		for(int i = 1; i <= tot; ++i)
			if((down[i] - up[i] + 1) * m == num[i]) {
				lu[up[i]] = ld[up[i]] = ru[up[i]] = rd[up[i]] = lr[up[i]] = false;
				lu[down[i]] = ld[down[i]] = ru[down[i]] = rd[down[i]] = lr[down[i]] = false;
				lr[up[i]] = true;
			}

		//debug
	    for(int i = 0; i < n; ++i)
			printf("%d %d %d %d %d\n", lu[i], ld[i], ru[i], rd[i], lr[i]);
		return tot - dp(lu, ld, ru, rd, lr);
	}  
  
};  
