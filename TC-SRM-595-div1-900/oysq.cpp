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
const double eps = 1e-6;

int n;
std::vector<int> x, y;
std::vector<double> p;

int det(int x1, int y1, int x2, int y2) {// 计算(x1, y1)和(x2, y2)的叉积
	return x1 * y2 - x2 * y1;
}

bool right(int u, int v, int w) {// 判断w是否在直线u -> v右边
	return det(x[v] - x[u], y[v] - y[u], x[w] - x[u], y[w] - y[u]) < 0;
}

#define sqr(x) ((x) * (x))

double dis(int u, int v) {// u, v两点距离
	return sqrt(sqr(x[u] - x[v]) + sqr(y[u] - y[v]));
}

bool onseg(int u, int v, int w) {// 判断w是否在线段u -> v上
	return det(x[v] - x[u], y[v] - y[u], x[w] - x[u], y[w] - y[u]) == 0 && fabs(dis(u, w) + dis(v, w) - dis(u, v)) < eps;
}

class Constellation {
public:
	double expectation(std::vector <int> _x, std::vector <int> _y, std::vector <int> prob) {
		x = _x, y = _y, p.clear();
		for(auto i : prob) p.pb(i / 1000.0);
		n = SZ(x);
		double ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(i != j) {// 计算每条边被算进答案的概率
					double c = p[i] * p[j];// 首先这两个点要被选
					for(int k = 0; k < n; ++k)// 其次所有在其右侧和线段上的点禁止选
						if(k != i && k != j)
							if(right(i, j, k) || onseg(i, j, k))
								c *= 1 - p[k];
					ans += c * det(x[i], y[i], x[j], y[j]);// 累计答案
				}
		return ans / 2;
	}
};
 