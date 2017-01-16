#line 2 "GearsDiv1.cpp"  
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
ll c[3];// 用二进制表示三种颜色的集合
int g[N + 9][N + 9];
bool vis[N + 9];
int mat[N + 9];

int dfs(int x, ll s) {
	for(int i = 0; i < n; ++i)
		if((s >> i & 1) && !vis[i] && g[x][i]) {
			vis[i] = true;
			if(mat[i] == -1 || dfs(mat[i], s)) {
				mat[i] = x;
				return 1;
			}
		}
	return 0;
}

int solve(ll s1, ll s2) {
	// 最大独立集 = n - maxmatch
	// ans = n - 最大独立集 = maxmatch
	int ret = 0;
	memset(mat, -1, sizeof mat);
	for(int i = 0; i < n; ++i)
		if(s1 >> i & 1) {
			memset(vis, false, sizeof vis);
			ret += dfs(i, s2);
		}
	return ret;
}

class GearsDiv1 {  
public:  
	int getmin(string color, vector <string> graph) {  
		n = SZ(color);
		for(int i = 0; i < n; ++i)
			if(color[i] == 'R') c[0] += 1ll << i;
			else if(color[i] == 'G') c[1] += 1ll << i;
			else c[2] += 1ll << i;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				g[i][j] = graph[i][j] == 'Y';
		// 假设给每个颜色分配一个方向，那么分到相同方向的齿轮如果相邻肯定不合法，于是求最大独立集即可
		// 但是同种颜色不相邻，因为三种颜色一起求最大独立集肯定没有两个求最大独立集优，于是变成了二分图最大独立集
		return std::min(std::min(solve(c[0], c[1]), solve(c[1], c[2])), solve(c[0], c[2]));
	}    
};  
