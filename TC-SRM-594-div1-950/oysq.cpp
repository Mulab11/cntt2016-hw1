// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndAvatar.cpp"
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

int w;
int ans;

bool onemove(int n, int x) {// 判断当n, x, w是否能一步走到
	if(n <= w && (!x || x == n - 1)) return true;
	if(w == 1 && !x) return true;
	if(x == w - 1 && n <= 2 * w - 1) return true;
	if(x == n - 1 && x % w == 0) return true;
	return false;
}

void dfs(int n, int x, int s) {// 当前状态n, x, s(步数)
	if(n == 1) {// 0步
		chkmin(ans, s);
		return ;
	}
	if(onemove(n, x)) {// 判断是否1步
		chkmin(ans, s + 1);
		return ;
	}
	if(s + 2 >= ans) return ;// 剪枝
	int r = x / w, c = x % w;
	for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= w; ++j)
			dfs(n - i * j, x - i * j, s + 1);// 顶上
	if((r + 1) * w < n) dfs((r + 1) * w, x, s + 1);// 下面
	int u = (n + w - 1) / w, v = (n - 1) % w + 1;
	// 左边
	for(int i = 1; i <= r + 1; ++i)
		for(int j = 1; j <= c; ++j)
			dfs(n - (u - i + 1) * j + (std::max(v, j) - v), x - (r + 1 - i + 1) * j, s + 1);
	// 右边
	for(int i = 1; i <= r; ++i)
		for(int j = c + 2; j <= w; ++j)
			dfs(n - (u - i) * (j - c - 1) - (std::min(std::max(v, c + 1), j) - c - 1), x - (r - i + 1) * (j - c - 1), s + 1);
}

struct FoxAndAvatar {
    int minimalSteps(int n, int width, int x) {
		w = width;
		ans = 4;// 答案最大是4，因此只需要判断答案是否 <= 3
		dfs(n, x - 1, 0);
		return ans;
    }
};
