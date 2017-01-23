#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, dx[6] = {-1, -1, 0, 0, 1, 1}, dy[6] = {0, 1, -1, 1, -1, 0};

class HexagonalBoard{
public:
	vector <string> g; int vis[MAXN][MAXN], ans, n;
	inline bool inMap(int i, int j){return i >= 0 && i < n && j >= 0 && j < n;}
	bool dfs(int x, int y, int c){
		ans = max(ans, c);
		if(vis[x][y] == -1) vis[x][y] = c;
		else return vis[x][y] == c;
		for(int i = 0; i < 6; ++ i){
			x += dx[i], y += dy[i];
			if(inMap(x, y) && g[x][y] == 'X' && !dfs(x, y, 3 - c))
				return false;
			x -= dx[i], y -= dy[i];
		} return true;
	}
	int minColors(vector <string> g_){
		int i, j; g = g_, n = g.size();
		memset(vis, -1, sizeof(vis));
		for(i = ans = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				if(g[i][j] == 'X' && vis[i][j] == -1 && !dfs(i, j, 1))
					return 3;
		return ans;
	}
};
