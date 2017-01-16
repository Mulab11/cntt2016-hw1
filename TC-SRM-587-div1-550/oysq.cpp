#line 2 "TriangleXor.cpp"  
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


class TriangleXor {  
public:
	int w;
	double tri(int u) {// 第u个三角形的面积
		return (double)u * w / 2 / (u + w);
	}
	double x(int u, int v) {// (0, 1)-(u, 0)与(v, 0)-(w, 1)的交点x坐标
		return (double)w * u / (w - v + u);
	}
	double y(int u, int v) {// ...y坐标
		return -x(u, v) / u + 1;
	}
	int theArea(int _w) {
		w = _w;
		double ans = 0;
		if(!(w & 1)) ans += w / 4.0;// 最上面的大三角形
		for(int i = 1; i <= w; i += 2)
			ans += 2 * (tri(i) - tri(i - 1));// 其余的三角形
		for(int i = 1; i < w; i += 2) {// 按层处理四边形
			double l = x(i, 0), r = x(w, w - i);
			ans += (r - l) * (y(i + 1, 0) - y(i, 1)) / 2;
		}
		return ans;
	}    
};  
