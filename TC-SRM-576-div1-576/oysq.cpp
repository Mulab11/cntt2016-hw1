// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheExperiment.cpp"
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

const int N = 300;
const int MOD = 1000000009;

std::string drop;
int f[N + 9][N + 9][2];// f[i][j] 表示右边界到i，已经用了j个海绵，当前连续的段中是否出现过覆盖长度为L的海绵
int g[N + 9][N + 9];// g[i][j] = sigma{f[k][j][1], k <= i}

struct TheExperiment {
    int countPlacements(vector <string> intensity, int M, int L, int A, int B) {
		drop.clear();
		for(int i = 0; i < SZ(intensity); ++i) drop += intensity[i];
		memset(f, 0, sizeof f), memset(g, 0, sizeof g);
		f[0][0][0] = 1;
		for(int i = 1; i <= SZ(drop); ++i) {
			f[i][0][0] = 1;
			for(int j = 1; j <= M; ++j) {
				for(int k = i - 1, sum = 0; i - k <= L && k >= 0; --k) {
					sum += drop[k] - '0';
					if(sum >= A && sum <= B) {
						int t = i - k == L;
						for(int p = 0; p < 2; ++p)
							(f[i][j][t | p] += f[k][j - 1][p]) %= MOD;// 当前海绵延续之前的海绵段
						if(k) (f[i][j][t] += g[k - 1][j - 1]) %= MOD;// 当前海绵为段的起始，要求之前的海绵段中至少有一个覆盖长度为L的海绵
					}
				}
			}
			for(int j = 0; j <= M; ++j)
				g[i][j] = (g[i - 1][j] + f[i][j][1]) % MOD;
		}
		int ans = 0;
		for(int i = 1; i <= SZ(drop); ++i)// 枚举最右端位置
			(ans += f[i][M][1]) %= MOD;
		return ans;
    }
};
