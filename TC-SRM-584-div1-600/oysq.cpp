#line 2 "Excavations.cpp"  
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

const int N = 50;

int n;
int v[N + 9], vn;
std::vector<int> d[N + 9];
bool in[N + 9];
ll C[N + 9][N + 9];
ll f[N + 9][N + 9][N + 9];

class Excavations {  
public:  
	long long count(vector <int> kind, vector <int> depth, vector <int> found, int K) {  
		n = SZ(kind);
		memset(in, false, sizeof in);
		for(auto i : found) in[i] = true;// 将found的类型标出来
		for(int i = 1; i <= 50; ++i) d[i].clear();
		// 将depth离散化
		vn = 0;
		for(int i = 0; i < n; ++i) v[++vn] = depth[i];
		std::sort(v + 1, v + vn + 1);
		vn = std::unique(v + 1, v + vn + 1) - v - 1;
		for(int i = 0; i < n; ++i) d[kind[i]].pb(depth[i] = std::lower_bound(v + 1, v + vn + 1, depth[i]) - v);// 将kind一样的放一起
		for(int i = 1; i <= 50; ++i) std::sort(d[i].begin(), d[i].end());// 同一个kind里面做一个depth排序
		// 预处理组合数
		for(int i = 0; i <= n; ++i) {
			C[i][0] = 1;
			for(int j = 1; j <= i; ++j)
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
		memset(f, 0, sizeof f);
		// dp : f[i][j][k]表示found中前i种type，一共用了j个site，depth最高为k的方案数
		f[0][0][0] = 1;
		for(int i = 0; i < SZ(found); ++i) {
			int k = found[i];
			for(int j = 0; j <= K; ++j)
				for(int h = 0; h <= vn; ++h)
					if(f[i][j][h]) {
						ll v = f[i][j][h];
						for(int p = 0; p < SZ(d[k]); ++p)
							for(int r = 1; r <= p + 1; ++r)
								f[i + 1][j + r][std::max(h, d[k][p])] += C[p][r - 1] * v;
					}
		}
		ll ans = 0;
		for(int j = 0; j <= K; ++j) {
			for(int h = 0; h <= vn; ++h) {
				ll cnt = 0;
				// 剩下K - j个site的选择
				if(j == K) cnt = 1;
				else {
					for(int t = h + 1; t <= vn; ++t) {// 枚举剩下的site的最小高度
						int cur = 0, ex = 0;
						for(int i = 0; i < n; ++i) {
							if(!in[kind[i]] && depth[i] == t) ex++;
							cur += depth[i] >= t;
						}
						// 最小的高度的site一定要有至少一个不在found里面的type，否则会重复计算
						for(int i = 1; i <= ex && i <= K - j; ++i) cnt += C[ex][i] * C[cur - ex][K - j - i];
					}
				}
				ans += cnt * f[SZ(found)][j][h];
			}
		}
		return ans;
	}  
};  
