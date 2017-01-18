#line 2 "RandomPaintingOnABoard.cpp"  
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

const int N = 12;
const int M = 21;
const int S = 1500;

int n, m;
int p[N + 9][M + 9], r[N + 9];
int f[2][S];

class RandomPaintingOnABoard {  
public:  
	double expectedSteps(vector <string> prob) {  
		n = SZ(prob), m = SZ(prob[0]);
		int sum = 0;
		// 令n <= m, 这样n <= 12
		if(n > m) {
			std::swap(n, m);
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j)
					p[i][j] = prob[j][i] - '0', sum += p[i][j];
		}
		else {
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j)
					p[i][j] = prob[i][j] - '0', sum += p[i][j];
		}
		// r[i] = sigma{p[i][j], j in [0, m)}
		for(int i = 0; i < n; ++i) {
			r[i] = 0;
			for(int j = 0; j < m; ++j)
				r[i] += p[i][j];
		}
		double ans = 0;
		for(int s = 0; s < (1 << n); ++s) {// 枚举行集合
			// f[b][i] 表示集合的大小奇偶性为b的情况下，概率为i / sum的集合数，背包dp
			for(int t = 0; t < 2; ++t)
				std::fill(f[t], f[t] + sum + 1, 0);
			int x = 0;
			for(int i = 0; i < n; ++i)
				if(s >> i & 1)
					x += r[i];
			f[__builtin_popcount(s) & 1][x] = 1;// 初始化
			for(int i = 0; i < m; ++i) {
				int g = 0;
				for(int j = 0; j < n; ++j)
					if(!(s >> j & 1))
						g += p[j][i];
				for(int j = sum - g; j >= 0; --j) {// 转移
					int u = f[0][j], v = f[1][j];
					f[0][j + g] += v, f[1][j + g] += u;
				}
			}
			// sigma{(1 - x) ^ i, i >= 0} = 1 / x
			for(int j = 1; j <= sum; ++j) {
				ans += (double)sum / j * f[1][j];
				ans -= (double)sum / j * f[0][j];
			}
		}
		return ans;
	}  
};  
