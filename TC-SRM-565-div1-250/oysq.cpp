// BEGIN CUT HERE

// END CUT HERE
#line 5 "MonstersValley.cpp"
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

const int N = 100;
const ll INF = 1e18;

int n;
ll f[N + 9][N + 9];// f[i][j] 表示前i只怪兽，花费了j的代价得到的最多的威胁值和

struct MonstersValley {
    int minimumPrice(vector<long long> dread, vector <int> price) {
		// 初始化
		for(int i = 0; i <= N; ++i)
			for(int j = 0; j <= N; ++j)
				f[i][j] = -INF;
		n = SZ(dread);
		f[0][price[0]] = dread[0];
		int sum = price[0];
		for(int i = 1; i < n; ++i) {
			sum += price[i];
			for(int j = 0; j <= sum; ++j) {
				if(j >= price[i]) chkmax(f[i][j], f[i - 1][j - price[i]] + dread[i]);// 花费代价贿赂
				if(f[i - 1][j] >= dread[i]) chkmax(f[i][j], f[i - 1][j]);// 不贿赂，但是要保证之前的和 > 当前怪兽的威胁值
			}
		}
		for(int i = 0; i <= sum; ++i)
			if(f[n - 1][i] >= 0) return i;// 扫到最小的有解的代价输出
		return -1;
	}
};
