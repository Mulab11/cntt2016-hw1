/#line 2 "SparseFactorial.cpp"  
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

const int LIM = 1e6;
const int INF = 1e9;

int p[LIM + 9], pn;
bool is[LIM + 9];
int minp[LIM + 9];

void euler() {
	pn = 0;
	for(int i = 2; i <= LIM; ++i) {
		if(!is[i]) p[++pn] = i, minp[i] = i;
		for(int j = 1; j <= pn && p[j] * i <= LIM; ++j) {
			int nex = p[j] * i;
			is[nex] = true;
			minp[nex] = p[j];
			if(i % p[j] == 0) break;
		}
	}
}

std::vector<int> f[LIM + 9];
int ans[LIM + 9];

void solve(int p, int c) {
	int n = 1;
	for(int i = 0; i < c; ++i) n *= p;
	f[p].clear(), f[p].resize(n, INF);// f[p][x]表示mod p^c = x的最小的k
	static int cnt[LIM], ind[LIM + 9];// cnt[i]表示i当前包含p的次数，ind[i]表示i中p的次数
	memset(cnt, 0, sizeof cnt);
	// 求出ind
	ind[0] = c, ind[1] = 0;
	for(int i = 2; i <= n; ++i)
		if(i % p == 0) ind[i] = ind[i / p] + 1;
		else ind[i] = 0;
	for(int k = 0; k <= p * c; ++k) {
		// 因为k和k + p影响的i是一样的，而且每次至少+1，而>=c之后的就没有意义了
		// 所以只有前p * c个k是有意义的
		int t = (ll)k * k % n;
		for(int j = 0; j != n; j += p) {// p ^ (c - 1)枚举i
			int i = (t + j) % n, ori = cnt[i];
			cnt[i] += ind[j];
			if(ori < c && cnt[i] >= c) f[p][i] = k;
		}
	}
}

ll get(ll n, int d, int i) {// 求出1 ~ n中，mod d = i的数的个数
	if(!n) return 0;
	return n / d + (n % d >= i) - (!i);
}

ll calc(ll n, ll d) {// 给定n, d求出个数
	ll ret = 0;
	for(int i = 0; i < d; ++i)
		if(ans[i] < INF && (ll)ans[i] * ans[i] < n)
			ret += get(n, d, i) - get((ll)ans[i] * ans[i], d, i);// 计算mod d = i的答案
	return ret;
}

class SparseFactorial {  
public:  
	ll getCount(ll lo, ll hi, ll d) {
		euler();// 欧拉筛法筛出所有数的最小质因子
		// 考虑到F(n) mod d = F(n + d) mod d，因此我们只要在mod d意义下考虑即可
		// 定义G(n, k) = (n - 0^2) * (n - 1^2) * ... * (n - k^2) mod d
		// 对于每个0 <= x < d，求出最小的k使得G(x, k) = 0即可
		std::fill(ans, ans + d, 0);// ans[i]表示对于x = i的最小的k，ans[i] = INF表示不存在这样的k
		// 因为d = p1^c1 * p2^c2 * ...
		// 所以可以转化成mod pi^ci，然后合并
		int td = d;
		while(td > 1) {
			int p = minp[td], c = 0, pc = td;
			while(td % p == 0) td /= p, c++;
			solve(p, c), pc /= td;// 处理mod p^c
			for(int i = 0; i < d; ++i)// 对每个0 <= i < d，用i % pc项来更新答案
				chkmax(ans[i], f[p][i % pc]);// 对每个质因子取最大值即可
		}
		return calc(hi, d) - calc(lo - 1, d);// 计算答案
	}    
};  
