#line 2 "ShoutterDiv1.cpp"  
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

const int N = 2500, INF = 0x3f3f3f3f;

int n, ans;
struct data {
	int l, r, id;
	data() {}
	data(int _l, int _r, int _id):l(_l), r(_r), id(_id) {}
}p[N + 9];
int f[N + 9], g[N + 9];
bool cmpr(const data &p, const data &q) {
	if(p.r == q.r) return p.l > q.l;
	else return p.r < q.r;
}

bool cmpl(const data &p, const data &q) {
	if(p.l == q.l) return p.r > q.r;
	else return p.l < q.l;
}
std::string con(std::vector<std::string> g) {
	std::string ret;
	for(int i = 0; i < SZ(g); ++i) ret += g[i];
	return ret;
}

class ShoutterDiv1 {
public:  
	int count(vector <string> _s1000, vector <string> _s100, vector <string> _s10, vector <string> _s1, vector <string> _t1000, vector <string> _t100, vector <string> _t10, vector <string> _t1) {
		std::string s1000 = con(_s1000), s100 = con(_s100), s10 = con(_s10), s1 = con(_s1);
		std::string t1000 = con(_t1000), t100 = con(_t100), t10 = con(_t10), t1 = con(_t1);
		n = SZ(s1), ans = 0;
		for(int i = 0; i < n; ++i) {
			int x, y;
			x = (s1000[i] - '0') * 1000 + (s100[i] - '0') * 100 + (s10[i] - '0') * 10 + (s1[i] - '0');
			y = (t1000[i] - '0') * 1000 + (t100[i] - '0') * 100 + (t10[i] - '0') * 10 + (t1[i] - '0');
			p[i] = data(x, y, i);
		}
		std::sort(p, p + n, cmpr);// 先按右端点排序
		memset(g, 0, sizeof g);
		for(int i = 0; i < n; ++i) {// dp出覆盖前i个点且必选第i个点的最小次数
			f[i] = INF;
			if(p[i].l <= p[0].r) f[i] = 1;
			else {
				for(int j = i - 1; j >= 0; --j)
					if(p[j].r >= p[i].l)
						chkmin(f[i], f[j] + 1);
			}
			g[p[i].id] += f[i];
		}
		std::sort(p, p + n, cmpl);// 再按左端点排序
		for(int i = n - 1; i >= 0; --i) {// dp出覆盖后i个点且必选第i个点的最小次数
			f[i] = INF;
			if(p[i].r >= p[n - 1].l) f[i] = 1;
			else {
				for(int j = i + 1; j < n; ++j)
					if(p[j].l <= p[i].r)
						chkmin(f[i], f[j] + 1);
			}
			g[p[i].id] += f[i] - 1;
		}
		// g[i]表示必选i的时候的最小答案
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j)// 考虑过从包含的区间转移的情况
				if(p[j].l <= p[i].l && p[i].r <= p[j].r)
					chkmin(g[p[i].id], g[p[j].id] + 1);
			if(g[p[i].id] >= INF) return -1;
			ans += g[p[i].id] - 1;
		}
		return ans;
	}   
};  
