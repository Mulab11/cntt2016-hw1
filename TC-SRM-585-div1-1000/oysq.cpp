#line 2 "EnclosingTriangle.cpp"  
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

const int M = 58585, N = M * 4, K = 20;

int n, k;
struct pot {// 定义向量(x, y)以及运算
	int x, y;
	pot(int _x = 0, int _y = 0):x(_x), y(_y) {}
	friend pot operator + (const pot &p, const pot &q) {
		return pot(p.x + q.x, p.y + q.y);
	}
	friend pot operator - (const pot &p, const pot &q) {
		return pot(p.x - q.x, p.y - q.y);
	}
	friend ll operator * (const pot &p, const pot &q) {
		return (ll)p.x * q.x + (ll)p.y * q.y;
	}
	friend ll operator ^ (const pot &p, const pot &q) {
		return (ll)p.x * q.y - (ll)p.y * q.x;
	}
}g[N + 9], h[K + 9];
pii p[N + 9];
ll pre[N + 9];

pii get(int id) {// 求出框上第id个点的两条将中间点集包含的线
	pot ma = g[(id + n - 1) % n] - g[id], mi = g[(id + 1) % n] - g[id], o = g[id];
	// 先搞出最大最小的向量
	for(int i = 0; i < k; ++i) {
		pot d = h[i] - o;
		if((d ^ ma) > 0) ma = d;
		if((mi ^ d) > 0) mi = d;
	}
	// 然后二分求出对应框上的点
	pii ret;
	int l = 1, r = n - 1;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		pot d = g[(id + mid) % n] - o;
		if((d ^ ma) >= 0) l = mid;
		else r = mid - 1;
	}
	ret.fi = (id + l) % n;
	l = 1, r = n - 1;
	while(l < r) {
		int mid = (l + r) >> 1;
		pot d = g[(id + mid) % n] - o;
		if((mi ^ d) >= 0) r = mid;
		else l = mid + 1;
	}
	ret.se = (id + l) % n;
	return ret;
}

bool in(int x, int l, int r) {// 判断x是否在逆时针区间l ~ r内
	if(l <= r) return l <= x && x <= r;
	else return l <= x || x <= r;
}

ll getpre(int l, int r) {// 逆时针区间l ~ r的和
	if(l <= r) return pre[r] - (l ? pre[l - 1] : 0);
	else return pre[n - 1] - (l ? pre[l - 1] : 0) + pre[r];
}

int dis(int l, int r) {// l ~ r的逆时针距离
	if(l <= r) return r - l;
	else return n - (l - r);
}

ll calc(int o, int l, int r) {// 第三个点起点为o，第二个点在l ~ r中的方案数
	ll ret = getpre(l, r);
	int u = 0, v = dis(l, r);
	while(u < v) {
		int mid = (u + v) >> 1;
		if(p[(l + mid) % n].fi < o) v = mid;
		else u = mid + 1;
	}
	if(p[(l + u) % n].fi < o) ret += (dis(l, r) - u + 1) * (ll)n;
	return ret - (dis(l, r) + 1) * (ll)(o - 1);
}

class EnclosingTriangle {  
public:  
	long long getNumber(int m, vector <int> x, vector <int> y) {  
		n = m * 4;
		k = SZ(x);
		for(int i = 0; i < k; ++i) h[i] = pot(x[i], y[i]);
		for(int i = 0; i < m; ++i) g[i] = pot(i, 0);
		for(int i = 0; i < m; ++i) g[i + m] = pot(m, i);
		for(int i = 0; i < m; ++i) g[i + m * 2] = pot(m - i, m);
		for(int i = 0; i < m; ++i) g[i + m * 3] = pot(0, m - i);
		for(int i = 0; i < n; ++i) p[i] = get(i), pre[i] = p[i].fi;
		for(int i = 1; i < n; ++i) pre[i] += pre[i - 1];// 对其中一条线做前缀和
		ll ans = 0;
		for(int i = 0, j = 1, k = 1; i < n; ++i) {// 枚举第一个点
			int u = p[i].fi, v = p[i].se;
			// j表示第二个点在j ~ u那么第三个点存在
			// k表示第二个点在k ~ u那么第三个点在k + 1 ~ i - 1 (只有当黑点个数为1的时候存在这种情况)
			while(!in(p[j].fi, v, (i + n - 1) % n) || i == j) (j += 1) %= n;
			while(!in(i, k, p[k].fi)) (k += 1) %= n;
			if(in(j, i, u)) {
				if(in(k, i, u)) ans += calc(v, j, (k + n - 1) % n);
				else ans += calc(v, j, u);
			}
			if(in(k, i, u)) ans += dis(v, i) - 1;
		}
		return ans / 3;
	}    
};  
