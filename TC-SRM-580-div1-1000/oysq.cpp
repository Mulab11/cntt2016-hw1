#line 2 "WallGameDiv1.cpp"  
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

int n, m;
int g[N + 9][N + 9];
int f[N + 9][N + 9];
int p[N + 9][N + 9][2];
int pre[N + 9];

int sum(int l, int r) {// 区间和
	return pre[r] - (l ? pre[l - 1] : 0);
}

int get(int l, int r, int d, int row) {// row行，封了的墙范围是[l, r], d = 0表示当前点在l，d = 1在r的答案
	if(l == 0 && r == m - 1) return 0;
	int &ret = p[l][r][d];
	if(ret != -1) return ret;// 记忆化
	int pos = !d ? l : r, a = INF, b = INF;
	if(l) a = sum(l - 1, pos - 1) + std::max(f[row + 1][l - 1], get(l - 1, r, 0, row)/* Eel选择最大的方案 */);
	if(r < m - 1) b = sum(pos + 1, r + 1) + std::max(f[row + 1][r + 1], get(l, r + 1, 1, row)/* Eel选择最大的方案 */);
	ret = std::min(a, b);// Rabbit选择最小的方案
	return ret;
}

class WallGameDiv1 {  
public:  
	int play(vector <string> costs) {
		n = SZ(costs), m = SZ(costs[0]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				g[i][j] = costs[i][j] - '0';
		for(int i = 0; i < m; ++i)
			f[n - 1][i] = g[n - 1][i];
		for(int i = n - 2; i >= 0; --i) {// 自底向上dp
			memset(pre, 0, sizeof pre);
			for(int j = 0; j < m; ++j)// 前缀和
				pre[j] = (j ? pre[j - 1] : 0) + g[i][j];
			memset(p, -1, sizeof p);
			for(int j = 0; j < m; ++j)
				f[i][j] = std::max(f[i + 1][j], get(j, j, 0, i)) + g[i][j];
		}
		int ans = INF;
		for(int i = 0; i < m; ++i)
			chkmin(ans, f[0][i]);
		return ans;
	}  	  
};  
