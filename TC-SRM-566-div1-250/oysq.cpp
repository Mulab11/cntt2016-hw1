// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinSledding.cpp"
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

const int N = 50;

struct PenguinSledding {
    long long countDesigns(int n, vector <int> c1, vector <int> c2) {
		// 答案 = 空集 + 边都从一个点出发的答案 + 三角形个数
		int cnt[N + 9] = {0};
		bool g[N + 9][N + 9] = {false};
		int m = SZ(c1);
		for(int i = 0; i < m; ++i) cnt[--c1[i]]++, cnt[--c2[i]]++, g[c1[i]][c2[i]] = g[c2[i]][c1[i]] = true;
		ll ans = 1;// 空集
		for(int i = 0; i < n; ++i) ans += (1ll << cnt[i]) - 1;// 从点i出发
		ans -= m;// 选一条边的方案被算了2次，因此要减掉
		// 减掉三角形个数
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				for(int k = j + 1; k < n; ++k)
					ans += g[i][j] && g[j][k] && g[k][i];
		return ans;
    }
};
