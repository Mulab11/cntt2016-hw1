#line 2 "ThreeColorability.cpp"  
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

int n, m;
int h[2][N + 9][N + 9];// h[0][i][j] > 0表示i行和j行相同，h[1][i][j] > 0表示i行和j行不相同
int col[N + 9];

bool dfs(int x, int c) {
	col[x] = c;
	for(int t = 0; t < 2; ++t)
		for(int y = 0; y < n; ++y)
			if(h[t][x][y]) {
				if(col[y] == -1) {
					if(!dfs(y, c ^ t))
						return false;
				}
				else if((col[x] ^ col[y]) != t)// 矛盾，返回-1
					return false;
			}
	return true;
}

bool check() {// 判断是否是二分图
	memset(col, -1, sizeof col);
	for(int i = 0; i < n; ++i)
		if(col[i] == -1)
			if(!dfs(i, 0))
				return false;
	return true;
}

class ThreeColorability {  
public:
	vector <string> lexSmallest(vector <string> g) {  
		n = SZ(g), m = SZ(g[0]);
		memset(h, 0, sizeof h);
		// 两行要么相同，要么相反
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(i != j) {
					int c[2] = {0};
					for(int k = 0; k < m; ++k)
						if(g[i][k] != '?' && g[j][k] != '?')
							c[g[i][k] == g[j][k]]++;
					// 根据已知信息连边
					if(c[1] && !c[0]) h[0][i][j]++;
					if(!c[1] && c[0]) h[1][i][j]++;
					if(c[0] && c[1]) return {};
				}
			}
		}
		if(!check()) return {};// 判断是否是二分图
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(g[i][j] == '?') {
					// 若填'N'
					for(int k = 0; k < n; ++k)
						if(i != k && g[k][j] != '?') {
							if(g[k][j] == 'N') h[0][i][k]++, h[0][k][i]++;
							else h[1][i][k]++, h[1][k][i]++;
						}
					if(check()) {
						g[i][j] = 'N';
						continue;
					}
					// 若填'Z'
					for(int k = 0; k < n; ++k)
						if(i != k && g[k][j] != '?') {
							if(g[k][j] == 'N') h[0][i][k]--, h[0][k][i]--, h[1][i][k]++, h[1][k][i]++;
							else h[1][i][k]--, h[1][k][i]--, h[0][i][k]++, h[0][k][i]++;
						}
					if(check()) {
						g[i][j] = 'Z';
						continue;
					}
					return {};
				}
		return g;
	}    
};  
