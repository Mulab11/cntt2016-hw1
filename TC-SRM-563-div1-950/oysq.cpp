#line 2 "CoinsGame.cpp"  
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

const int N = 40;
const int MOD = 1000000009;
const int d[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int n, m;
std::vector<std::string> g;
struct data {
	int x1, y1, x2, y2;
	data() {}
	data(int _x1, int _y1, int _x2, int _y2):x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};
std::queue<data> q;
bool f[N][N][N][N];// f[i][j][k][r] = true表示(i, j)和(k, r)是否能有一个在外，一个在内

int id[N][N], tot;// id[i][j] 表示(i, j)的编号
int fa[N * N], sz[N * N];// fa[i] 表示并查集fa[i]的父亲，sz[i]表示并查集中i子树的大小

int pw[N * N + 1];// pw[i] 表示 2 ^ i

int out(int x, int y) {// 判断(x, y)是否在矩形外
	return x < 0 || x >= n || y < 0 || y >= m;
}

bool check(int x1, int y1, int x2, int y2) {// 检测(x1, y1), (x2, y2)是否走一步能让两个点一个在外一个在内
	for(int i = 0; i < 4; ++i) {
		int tx1 = x1 + d[i][0], ty1 = y1 + d[i][1];
		int tx2 = x2 + d[i][0], ty2 = y2 + d[i][1];
		if(out(tx1, ty1) + out(tx2, ty2) == 1)
			return true;
	}
	return false;
}

bool move(int x1, int y1, int x2, int y2, int i) {// (x1, y1) 向方向i走一步，判断是不是到(x2, y2)
	if(!out(x1 + d[i][0], y1 + d[i][1])) {
		if(g[x1 + d[i][0]][y1 + d[i][1]] == '.') return x2 == x1 + d[i][0] && y2 == y1 + d[i][1];
		else return x2 == x1 && y2 == y1;
	}
	else return false;
}

int find(int x) {// 并查集找根
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

class CoinsGame {  
public:  
	int ways(vector <string> _g) {
		g = _g, n = SZ(g), m = SZ(g[0]);
		memset(f, false, sizeof f);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				for(int k = 0; k < n; ++k)
					for(int r = 0; r < m; ++r)
						if(!(i == k && j == r)) {
							if(g[i][j] == '.' && g[k][r] == '.') {
								if(check(i, j, k, r)) {
									// 初始边界状态
									f[i][j][k][r] = true;
									q.push(data(i, j, k, r));
								}
							}
						}
		// BFS
		while(!q.empty()) {
			data p = q.front();q.pop();
			for(int i = 0; i < 4; ++i) {
				int tx1, ty1, tx2, ty2;
				for(int u = -1; u < 1; ++u)
					for(int v = -1; v < 1; ++v) {
						tx1 = p.x1 + u * d[i][0];
						ty1 = p.y1 + u * d[i][1];
						tx2 = p.x2 + v * d[i][0];
						ty2 = p.y2 + v * d[i][1];
						if(!out(tx1, ty1) && !out(tx2, ty2)) {
							if(move(tx1, ty1, p.x1, p.y1, i) && move(tx2, ty2, p.x2, p.y2, i))
								if(!f[tx1][ty1][tx2][ty2]) {
									f[tx1][ty1][tx2][ty2] = true;
									q.push(data(tx1, ty1, tx2, ty2));
								}
						}
					}
			}
		}
		tot = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(g[i][j] == '.')
					fa[tot] = tot, sz[tot] = 1, id[i][j] = tot++;// 确定边界，初始化并查集
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				for(int k = 0; k < n; ++k)
					for(int r = 0; r < m; ++r)
						if(g[i][j] == '.' && g[k][r] == '.' && !f[i][j][k][r]) {
							// 将不能一个在外一个在内的点对并起来
							int u = find(id[i][j]), v = find(id[k][r]);
							if(u != v) fa[u] = v, sz[v] += sz[u];
						}
		pw[0] = 1;
		for(int i = 1; i <= tot; ++i) pw[i] = (ll)pw[i - 1] * 2 % MOD;
		// 答案 = (2 ^ 空白点个数 - 1) - sigma{2 ^ 并查集每个集合的大小 - 1}
		int ans = (pw[tot] + MOD - 1) % MOD;
		for(int i = 0; i < tot; ++i)
			if(find(i) == i)
				(ans += MOD - pw[sz[i]] + 1) %= MOD;
		return ans;
	}  
};  
