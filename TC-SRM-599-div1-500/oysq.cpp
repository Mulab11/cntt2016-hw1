// BEGIN CUT HERE

// END CUT HERE
#line 5 "FindPolygons.cpp"
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

const int MAX = 5000;
const int D[2] = {-1, 1};

int sqr(int x) {
	return x * x;
}

struct FindPolygons {
    double minimumPolygon(int L) {
		if(L & 1) return -1;// L是奇数无解
		int ans = -1;
		std::vector<pii> p;
		std::vector<int> l;
		for(int a = 1; 3 * a <= L; ++a)
			for(int b = 1; a + b <= L; ++b) {
				int c = sqrt(a * a + b * b);
				// 避免精度误差
				if(sqr(a) + sqr(b) == sqr(c - 1)) c--;
				if(sqr(a) + sqr(b) == sqr(c + 1)) c++;
				if(sqr(a) + sqr(b) == sqr(c) && c <= L) {
					p.pb(mp(a, b)), l.pb(c);// 将所有斜边算出来
					if(a + b + c == L) {// 判断是否是直角三角形
						if(ans == -1) ans = c - std::min(a, b);
						else chkmin(ans, c - std::min(a, b));
					}
				}
			}
		for(int i = 0; i < SZ(p); ++i)// 如果不是直角三角形，那么必定有至少两条斜边
			for(int a = 0; a < 2; ++a)
				for(int b = 0; b < 2; ++b)// 枚举第一条斜边的方向，一个斜边有4种方向，(p[i].fi * {-1, 1}, p[i].se * {-1, 1})
					for(int j = i; j < SZ(p); ++j) {
						int res = L - l[i] - l[j];// res 表示第3边的长度
						if(res <= 0) continue;// 长度都是正数
						// 任意两边之和大于第三边
						if(l[i] + l[j] <= res) continue;
						if(l[i] + res <= l[j]) continue;
						if(res + l[j] <= l[i]) continue;
						// 最大最小值
						int max = std::max(std::max(l[i], l[j]), res);
						int min = std::min(std::min(l[i], l[j]), res);
						for(int c = 0; c < 2; ++c)
							for(int d = 0; d < 2; ++d) {// 枚举第二条斜边的方向
								// x, y表示第三条边的向量的两维的绝对值
								int x = abs(p[i].fi * D[a] + p[j].fi * D[c]);
								int y = abs(p[i].se * D[b] + p[j].se * D[d]);
								if(x * x + y * y == res * res) {// 判断长度和向量是否满足条件
									if(ans == -1) ans = max - min;
									else chkmin(ans, max - min);
								}
							}
					}
		if(ans != -1) return ans;
		// 否则是四边形
		int len = L >> 1;
		if(len > 1) return len & 1;
		else return -1;
    }
};
