#line 2 "CentaurCompany.cpp"  
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

const int N = 36;

int n;
std::vector<int> adj[N + 9];
int fa[N + 9];
std::vector<int> ord;// 按dfs序排序的点

ll f[N + 9][2 * N + 9][2];
// f[i][j][0/1] 表示以i为根的子树中，选中的点构成的联通块个数 * 2 - 选中的点数 = j - n, 根i是否选的方案数, -n是为了保证j的范围在[0, 2n]内
// 因为max(选中的点构成的联通块个数 * 2 - 选中的点数 - 2, 0)就是一种方案的最少代价

void dfs(int x) {
	ord.pb(x);
	for(auto y : adj[x]) {
		if(y != fa[x]) {
			fa[y] = x;
			dfs(y);
		}
	}
}

class CentaurCompany {  
public:  
	double getvalue(vector <int> a, vector <int> b) {  
		n = SZ(a) + 1;
		for(int i = 1; i <= n; ++i) {
			adj[i].clear();
		}
		for(int i = 0; i < n - 1; ++i) {
			adj[a[i]].pb(b[i]);
			adj[b[i]].pb(a[i]);
		}
		fa[1] = 0;
		ord.clear();
		dfs(1);
		memset(f, 0, sizeof f);
		for(int i = 1; i <= n; ++i) {// 初始化，只有根节点一个点
			f[i][n][0] = 1;
			f[i][n + 1][1] = 1;
		}
		for(int i = n - 1; i >= 0; --i) {// dfs序从后往前dp
			int x = ord[i];
			int y = fa[x];
			static ll h[2 * N + 9][2];
			memset(h, 0, sizeof h);
			for(int j = -n; j <= n; ++j) {
				for(int k = -n; k <= n; ++k) {
					if(k + j >= -n && k + j <= n) {// 不用合并联通块
						h[j + k + n][0] += (f[x][j + n][0] + f[x][j + n][1]) * f[y][k + n][0];
						h[j + k + n][1] += f[x][j + n][0] * f[y][k + n][1];
					}
					if(k + j - 2 >= -n && k + j - 2 <= n) {// 合并联通块
						h[j + k - 2 + n][1] += f[x][j + n][1] * f[y][k + n][1];
					}
				}
			}
			memcpy(f[y], h, sizeof h);
		}
		double ans = 0;
		for(int i = 0; i <= 2 * n; ++i) {// 统计答案
			ans += std::max(0, i - 2 - n) * (f[1][i][0] + f[1][i][1]);
		}
		return 2 * ans / (double)(1ll << n);// 因为两种点的方案对称，因此 * 2
	}   
};  
