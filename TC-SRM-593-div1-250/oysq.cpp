#line 2 "HexagonalBoard.cpp"  
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

int n;
std::vector<std::string> g;
int c[N + 9][N + 9], sz;

bool dfs(int x, int y, int col) {// dfs判断是否是二分图
	c[x][y] = col, sz++;
	for(int i = -1; i <= 1; ++i)
		for(int j = -1; j <= 1; ++j)
			if(i != j) {
				int u = x + i, v = y + j;
				if(u < 0 || u >= n || v < 0 || v >= n || g[u][v] != 'X') continue;
				if(c[u][v] == -1) {
					if(!dfs(u, v, col ^ 1)) return false;
				}
				else if(c[u][v] == c[x][y]) return false;
			}
	return true;
}

class HexagonalBoard {  
public:  
	int minColors(vector <string> board) {
		// 由于对于一个全是X的图，最多只要三种颜色就可以了，因此我们只要判断答案为1,2,3即可
		g = board, n = SZ(g);
		memset(c, -1, sizeof c);
		int ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(g[i][j] == 'X' && c[i][j] == -1) {
					sz = 0;
					if(dfs(i, j, 0)) {// 若是二分图，该联通块答案 < 3
						if(sz == 1) chkmax(ans, 1);// 联通块只有一个点答案 = 1
						else chkmax(ans, 2);// 否则 = 2
					}
					else chkmax(ans, 3);// 否则该联通块的答案 = 3
				}
		return ans;
	}  
};  
