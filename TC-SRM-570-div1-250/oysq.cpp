#line 2 "RobotHerb.cpp"  
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

const int d[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
// d[0, 1, 2, 3] 分别代表上右下左

int dir;
std::vector<int> a;

pii get(int t) {// 从方向t出发的位移
	dir = t;
	int x = 0, y = 0;
	for(int i = 0; i < SZ(a); ++i) {
		x += a[i] * d[dir][0];
		y += a[i] * d[dir][1];
		(dir += a[i]) %= 4;
	}
	return mp(x, y);
}

class RobotHerb {  
public:  
	long long getdist(int T, vector <int> _a) {
		a = _a;
		int t = 0;
		pii tmp, g[5];
		bool v[4] = {false};// 标记是否走过
		int l = 0;// 循环节长度
		while(!v[t]) {// 找方向的循环节，每一步的位移记在g中
			v[t] = true;
			tmp = get(t), ++l;
			g[l].fi = g[l - 1].fi + tmp.fi, g[l].se = g[l - 1].se + tmp.se;
			t = dir;
		}
		ll x = (ll)(T / l) * g[l].fi + g[T % l].fi, y = (ll)(T / l) * g[l].se + g[T % l].se;// 一个循环节的总位移是一样的可以一起算
		return abs(x) + abs(y);
	}  
};  
