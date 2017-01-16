#line 2 "EqualSums.cpp"  
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
const int MOD = 1000000007;

int n;
std::vector<std::string> g;

std::vector<int> r, c;
bool vis[N + 9][2];

int x[N + 9], y[N + 9];

bool dfs(int i, int f) {
	// f = 0表示行i，f = 1表示列i
	vis[i][f] = true;// 标记，避免重复经过
	// 将联通块存下来，行为r，列为c
	if(!f) r.pb(i);
	else c.pb(i);
	// 设初始行为v，那么每一行的值为x[i] + v，每一列的值为y[i] - v
	for(int ni = 0; ni < n; ++ni)
		if(!vis[ni][!f]) {
			char c = !f ? g[i][ni] : g[ni][i];
			if(c >= '0' && c <= '9') {
				if(!f) y[ni] = c - '0' - x[i];
				else x[ni] = c - '0' - y[i];
				if(!dfs(ni, !f)) return false;
			}
		}
		else {
			char c = !f ? g[i][ni] : g[ni][i];
			if(c >= '0' && c <= '9') {
				// 判断能否满足预设条件
				if(!f) {
					if(x[i] + y[ni] != c - '0')
						return false;
				}
				else {
					if(y[i] + x[ni] != c - '0')
						return false;
				}
			}
		}
	return true;
}

class EqualSums {  
public:  
	int count(vector <string> _g) {
		g = _g, n = SZ(g[0]);
		memset(vis, false, sizeof vis);
		memset(x, 0, sizeof x), memset(y, 0, sizeof y);
		int p1 = 1, p2 = 1;
		for(int i = 0; i < n; ++i) {
			if(vis[i][0]) continue;
			// 枚举行列的联通快
			r.clear(), c.clear();
			if(!dfs(i, 0)) return 0;// 无法构成题目中预设的一些位置的值
			int lb = 0, ub = 9;// lb, ub分别为当前行的值的上下界
			for(int j = 0; j < SZ(r); ++j) chkmax(lb, -x[r[j]]);
			for(int j = 0; j < SZ(c); ++j) chkmin(ub, y[c[j]]);
			if(lb > ub) return 0;// 无解
			p1 = (ll)p1 * (ub - lb + 1) % MOD;// p1 表示每个联通快任意取值的数量
			p2 = (ll)p2 * (ub - lb) % MOD;// p2 表示每个联通快行都不为0的数量
		}
		return (p1 - p2 + MOD) % MOD;// 答案就是至少有一个行为0的方案数
	}  
};  
