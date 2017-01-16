// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheDevice.cpp"
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

struct TheDevice {
    int minimumAdditional(vector <string> plates) {
		// 每个位置如果要判断是or/and/xor的话，至少要有一个0，两个1
		int n = SZ(plates), m = SZ(plates[0]), ans = 0;
		for(int j = 0; j < m; ++j) {
			int c[2] = {0};
			for(int i = 0; i < n; ++i)
				c[plates[i][j] - '0']++;
			chkmax(ans, std::max(0, 1 - c[0]) + std::max(0, 2 - c[1]));
		}
		return ans;
    }
};
