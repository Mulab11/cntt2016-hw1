// BEGIN CUT HERE

// END CUT HERE
#line 5 "BallsSeparating.cpp"
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

const int INF = 0x3f3f3f3f;

struct BallsSeparating {
    int minOperations(vector <int> red, vector <int> green, vector <int> blue) {
		int n = SZ(red);
		int ans = INF;
		// 枚举最后为red，green，blue的三个位置
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k < n; ++k)
					if(i != j && j != k && k != i) {
						int cur = 0;
						// 处理i, j, k的贡献
						cur += green[i] + blue[i];
						cur += red[j] + blue[j];
						cur += red[k] + green[k];
						// 处理其他的贡献
						for(int r = 0; r < n; ++r)
							if(r != i && r != j && r != k)
								cur += red[r] + green[r] + blue[r] - std::max(red[r], std::max(green[r], blue[r]));
						chkmin(ans, cur);
					}
		if(ans == INF) return -1;// 无解
		else return ans;
    }
};
