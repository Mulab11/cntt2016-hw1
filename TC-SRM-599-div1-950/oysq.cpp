#line 2 "SimilarNames.cpp"  
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

const int N = 50, M = 16;
const int MOD = 1000000007;

int n, m, pn, p[M + 9];
std::vector<int> adj[N + 9];
std::vector<int> vld;
bool ok[1 << M];
std::vector<int> sub[1 << M];
int f[N + 9][1 << M], g[1 << M];

bool prefix(std::string a, std::string b) {// 判断a是否是b的前缀
	return SZ(a) < SZ(b) && b.substr(0, SZ(a)) == a;
}

bool cmp(const std::string &a, const std::string &b) {// 判断a的长度是否<b的长度
	return SZ(a) < SZ(b);
}

void dp(int x) {
	f[x][0] = 1;
	for(auto c : adj[x]) {
		dp(c);
		std::copy(f[x], f[x] + (1 << pn), g);
		std::fill(f[x], f[x] + (1 << pn), 0);
		for(auto s : vld)
			for(auto t : sub[s])// 枚举子集转移
				(f[x][s] += (ll)g[t] * f[c][s - t] % MOD) %= MOD;
	}
	if(x < n) {
		std::copy(f[x], f[x] + (1 << pn), g);
		std::fill(f[x], f[x] + (1 << pn), 0);
		for(auto s : vld) {
			f[x][s] = g[s];// 根不放在特殊位置上
			for(int i = s; i; i -= i & -i)// 枚举根放在哪个特殊位置上
				(f[x][s] += g[s - (i & -i)]) %= MOD;
		}
	}
}

class SimilarNames {  
public:  
	int count(vector <string> str, vector <int> a, vector <int> b) {
		n = SZ(str), m = SZ(a);
		std::sort(str.begin(), str.end(), cmp);// 根据长度排序后，某个字符串的父亲就是最长的是它的前缀的串
		for(int i = 0; i < n; ++i) {
			int fa = n;// 如果没找到，那就连到一个新的空节点
			for(int j = i - 1; j >= 0; --j)
				if(prefix(str[j], str[i])) {// 找到最长的前缀
					fa = j;
					break;
				}
			adj[fa].pb(i);
		}
		// 离散化a和b
		for(auto i : a) p[++pn] = i;
		for(auto i : b) p[++pn] = i;
		std::sort(p + 1, p + pn + 1);
		pn = std::unique(p + 1, p + pn + 1) - p - 1;
		for(int i = 0; i < m; ++i) {
			a[i] = std::lower_bound(p + 1, p + pn + 1, a[i]) - p - 1;
			b[i] = std::lower_bound(p + 1, p + pn + 1, b[i]) - p - 1;
		}
		// 将所有的合法状态提出来，因为如果a是b的前缀，那么a在树中的位置一定是b的位置的祖先
		for(int i = 0; i < (1 << pn); ++i) {
			bool f = true;
			for(int j = 0; j < m; ++j)
				if((i >> a[j] & 1) && !(i >> b[j] & 1)) {// 不可能出现只有a而没有b的情况
					f = false;
					break;
				}
			if(f) vld.pb(i), ok[i] = true;// ok[i]表示i是否合法，vld存储了所有合法的状态
		}
		for(auto s : vld)// 将每个合法状态的合法子状态提出来
			for(int t = s; ; t = (t - 1) & s) {
				if(ok[t] && ok[s - t]) sub[s].pb(t);
				if(!t) break;
			}
		dp(n);
		int ans = f[n][(1 << pn) - 1];
		for(int i = 1; i <= n - pn; ++i) ans = (ll)ans * i % MOD;// 剩下的n - pn个数随意放
		return ans;
	}
};
