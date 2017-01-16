#line 5 "NextAndPrev.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int m = 26;
const int INF = 1e9;

int solve(std::vector<int> f, int nextCost, int prevCost) {// 对于一个给定的匹配f，求最小代价
	int last = -INF;
	for(int i = 0; i < m; ++i) {
		if(f[i] != -INF) {
			if(f[i] < last) {// 有匹配边交叉，无解
				return INF;
			}
			last = f[i];
		}
	}
	int ret = 0;
	for(int i = 0; i < m; ++i) {
		if(f[i] != -INF) {
			int j = i, p = i, q = i;// p, q表示值 = f[i]的区间的左右边界
			while(j < m - 1 && (f[j + 1] == -INF || f[j + 1] == f[i])) {
				++j;
				if(f[j] == f[i]) {
					q = j;
				}
			}
			chkmin(p, f[i]);
			chkmax(q, f[i]);
			// 相同的值可以一起计算贡献
			ret += (f[i] - p) * nextCost;
			ret += (q - f[i]) * prevCost;
			i = j;
		}
	}
	return ret;
}

struct NextAndPrev {
    int getMinimum(int nextCost, int prevCost, string start, string goal) {
		if(start == goal) return 0;// 相等直接返回0
		int n;
		std::vector<int> f;// start -> goal的匹配关系
		n = SZ(start);
		f.resize(m, -INF);
		std::set<int> s;// goal的字符集大小
		for(int i = 0; i < n; ++i) {
			int x = start[i] - 'a';
			int y = goal[i] - 'a';
			s.insert(y);
			if(f[x] != -INF && f[x] != y) {
				return -1;// start中的一个字符只能匹配goal中的一个字符
			}
			f[x] = y;
		}
		bool flag = false;
		for(int i = 0; i < m; ++i) {
			if(f[i] == -INF) {
				flag = true;
			}
		}
		if(!flag && SZ(s) == m) {
			return -1;// 两边都有满的26个字符集的时候，没办法移动
		}
		int ans = INF;
		for(int sh = 0; sh < m; ++sh) {// 枚举移动距离
			// x, y, z枚举三种位置关系取最小的
			std::vector<int> x(m);
			for(int i = 0; i < m; ++i) {
				x[(i + sh) % m] = f[i] == -INF ? -INF : f[i] + sh;
			}
			chkmin(ans, solve(x, nextCost, prevCost));
			std::vector<int> y(m);
			for(int i = 0; i < m; ++i) {
				y[i] = x[i] == -INF ? -INF : x[i] + m;
			}
			chkmin(ans, solve(y, nextCost, prevCost));
			std::vector<int> z(m);
			for(int i = 0; i < m; ++i) {
				z[i] = x[i] == -INF ? -INF : x[i] - m;
			}
			chkmin(ans, solve(z, nextCost, prevCost));
		}
		return ans == INF ? -1 : ans;
    }
};
