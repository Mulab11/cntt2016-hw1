#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int N = 50;
const int X = 1e5;

ll ceil(ll a, ll b) {// a / b向下取整
	if(a >= 0) return (a + b - 1) / b;
	else return -((-a) / b);
}

ll floor(ll a, ll b) {// a / b向上取整
	if(a >= 0) return a / b;
	else return -ceil(-a, b);
}

class ConvexPolygonGame {
public:
	std::string winner(std::vector<int> x, std::vector<int> y) {
		static pii t[2 * X + 1];
		for(int i = 0; i <= 2 * X; ++i) t[i] = mp(0, -1);// 维护每个横坐标x对应的y坐标的范围
		for(int i = 0; i < SZ(x); ++i) x[i] += X;// 使x为非负整数
		int n = SZ(x);
		for(int i = 0; i < n; ++i) {
			int j = (i + 1) % n;// 连线i->j
			if(x[i] == x[j]) t[x[i]] = mp(std::min(y[i], y[j]) + 1, std::max(y[i], y[j]) - 1);// 竖边
			else if(x[i] < x[j]) {// 凸包下边界
				t[x[i]].fi = y[i] + 1, t[x[j]].fi = y[j] + 1;// 不能顶点重合
				for(int k = x[i] + 1; k < x[j]; ++k)
					t[k].fi = ceil((ll)(k - x[i]) * (y[j] - y[i]) + (ll)y[i] * (x[j] - x[i]), x[j] - x[i]);// 相似算出纵坐标
			}
			else {// 凸包上边界
				t[x[i]].se = y[i] - 1, t[x[j]].se = y[j] - 1;// 不能顶点重合
				for(int k = x[j] + 1; k < x[i]; ++k)
					t[k].se = floor((ll)(k - x[j]) * (y[i] - y[j]) + (ll)y[j] * (x[i] - x[j]), x[i] - x[j]);// 相似算出纵坐标
			}
		}
		// 如果能找到一个极小的三角形，那么Masha胜利
		std::vector<pii> two;
		for(int i = 0; i <= 2 * X; ++i) {
			for(int j = t[i].fi; j <= t[i].se; ++j) {
				two.pb(mp(i, j));
				if(SZ(two) == 2) break;
			}
			if(SZ(two) == 2) break;
		}
		if(SZ(two) < 2) return "Petya";// 点数 < 2 找不到三角形 Petya胜利
		for(int i = 0; i <= 2 * X; ++i)
			for(int j = t[i].fi; j <= t[i].se; ++j)
				if((ll)(i - two[0].fi) * (two[1].se - two[0].se) - (ll)(two[1].fi - two[0].fi) * (j - two[0].se))
					return "Masha";// 找到了Masha胜利
		return "Petya";// 否则Petya胜利
	}
};
