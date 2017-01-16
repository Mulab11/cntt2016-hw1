// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysChessboard.cpp"
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

const int INF = 0x3f3f3f3f;

std::vector<pii> p;
int f[17][17][17][17];

bool in(const pii &p, int x1, int x2, int y1, int y2) {// 判断点p在不在矩形(x1, y1) - (x2, y2)内
	return x1 <= p.fi && p.fi <= x2 && y1 <= p.se && p.se <= y2;
}

int dp(int x1, int x2, int y1, int y2) {// f[x1][x2][y1][y2] 表示将不在矩形(x1, y1) - (x2, y2)内的点加入进去的最小代价
	int &ret = f[x1][x2][y1][y2];
	if(ret != -1) return ret;
	ret = INF;
	bool flag = false;
	for(int i = 0; i < SZ(p); ++i)
		if(!in(p[i], x1, x2, y1, y2)) {// 枚举下一个加入的点
			flag = true;
			int nx1 = std::min(x1, p[i].fi), nx2 = std::max(x2, p[i].fi);
			int ny1 = std::min(y1, p[i].se), ny2 = std::max(y2, p[i].se);
			int cost = 0;
			for(int j = 0; j < SZ(p); ++j)
				if(in(p[j], nx1, nx2, ny1, ny2) && !in(p[j], x1, x2, y1, y2))
					cost += std::max(std::max(p[j].fi - nx1, nx2 - p[j].fi), std::max(p[j].se - ny1, ny2 - p[j].se));// 计算代价
			chkmin(ret, cost + dp(nx1, nx2, ny1, ny2));
		}
	if(!flag) ret = 0;
	return ret;
}

struct EllysChessboard {
    int minCost(vector <string> board) {
		p.clear();
		for(int i = 0; i < SZ(board); ++i)
			for(int j = 0; j < SZ(board[i]); ++j)
				if(board[i][j] == '#')
					p.pb(mp(i + j, i - j + 8));// 坐标变换，转45°，方便计算
		if(!SZ(p)) return 0;
		memset(f, -1, sizeof f);
		int ans = INF;
		for(int i = 0; i < SZ(p); ++i)
			chkmin(ans, dp(p[i].fi, p[i].fi, p[i].se, p[i].se));// 枚举第一个加入的点
		return ans;
	}
};
