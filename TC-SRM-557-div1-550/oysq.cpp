#line 2 "Incubator.cpp"  
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
const int INF = 1e9;

int n;
int g[N + 9][N + 9];
int mat[N + 9];
bool vis[N + 9];

// find augment path
int dfs(int x) {
	for(int i = 0; i < n; ++i)
		if(!vis[i] && g[x][i] != INF) {
			vis[i] = true;
			if(mat[i] == -1 || dfs(mat[i])) {
				mat[i] = x;
				return 1;
			}
		}
	return 0;
}

class Incubator {  
public:
	// Dilworth's theorem
	// maximal antichain = minimal chain covering
	int maxMagicalGirls(vector <string> love) {  
		n = SZ(love);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(love[i][j] == 'Y') g[i][j] = 1;
				else g[i][j] = INF;
		// transitive closure
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					chkmin(g[i][j], g[i][k] + g[k][j]);
		int match = 0;
		memset(mat, -1, sizeof mat);
		// bipartite graph matching
		for(int i = 0; i < n; ++i) {
			memset(vis, false, sizeof vis);
			match += dfs(i);
		}
		return n - match;
	}    
};  
