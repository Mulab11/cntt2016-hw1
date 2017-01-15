// BEGIN CUT HERE

// END CUT HERE
#line 5 "Mountains.cpp"
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

const int N = 10;
const int W = 50;
const int MOD = 1000000009;

int n, w;
bool vis[N + 9][W + 9];// vis[i][j] = true 表示第i座山在第j列可以看到
std::vector<int> h;// 每个山顶的高度

std::map<std::vector<int>, int> f[N + 9];// f[i][v] 表示倒着放到第i座山时状态为v的方案数

int dp(int x, const std::vector<int> &a) {// x表示当前处理第i座山，a表示每列的高度
	if(x == -1) return 1;
	if(f[x].count(a)) return f[x][a];// 记忆化搜索
	int &ret = f[x][a];
	std::vector<int> na;
	for(int i = 0; i < w; ++i) {// 枚举山顶的列坐标
		bool flag = true;
		for(int j = 0; j < w; ++j)
			if((h[x] - abs(j - i) <= a[j]) == vis[x][j]) {// 判断是否满足题意
				flag = false;
				break;
			}
		if(flag) {
			na = a;
			for(int j = 0; j < w; ++j)
				chkmax(na[j], h[x] - abs(j - i));
			(ret += dp(x - 1, na)) %= MOD;
		}
	}
	return ret;
}

struct Mountains {
    int countPlacements(vector <int> _h, vector <string> v) {
		h = _h, n = SZ(h), w = SZ(v[0]);
		for(int i = 0; i < n; ++i) f[i].clear();
		
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < w; ++j)
				if(v[i][j] == 'X')
					vis[i][j] = true;
				else
					vis[i][j] = false;

		std::vector<int> t;
		for(int i = 0; i < w; ++i) t.pb(0);// 初始每列的高度为0

		return dp(n - 1, t);
    }
};
