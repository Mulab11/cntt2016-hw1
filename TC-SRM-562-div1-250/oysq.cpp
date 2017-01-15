// BEGIN CUT HERE

// END CUT HERE
#line 5 "PastingPaintingDivOne.cpp"
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

const int N = 50, M = 50;

int n, m;// 行数和列数

int tran(int x, int y) {// 颜色x被颜色y覆盖之后的结果，如果y = 0(透明)那么不变，否则变为y
	if(y) return y;
	else return x;
}

int id(char c) {// 透明为0，R,G,B分别为1,2,3
	if(c == '.') return 0;
	else if(c == 'R') return 1;
	else if(c == 'G') return 2;
	else return 3;
}

struct PastingPaintingDivOne {
    vector<long long> countColors(vector <string> g, int T) {
		n = SZ(g), m = SZ(g[0]);
		vector<ll> ret;
		ret.resize(3, 0);
		// 一个点被覆盖多次相当于(x, y)被(x - 1, y - 1), (x - 2, y - 2), (x - 3, y - 3)... 覆盖
		for(int i = 0; i < n - 1; ++i)
			for(int j = 0; j < m - 1; ++j) {// 不在右下边界上的点只会被考虑一次
				int cur = 0;
				for(int k = 0; k <= i && k <= j && k < T; ++k)
					cur = tran(cur, id(g[i - k][j - k]));// 暴力模拟
				if(cur) ret[cur - 1]++;
			}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(i == n - 1 || j == m - 1) {// 右下边界上的点会被考虑T次，因为每次扩展新的点都是右下边界上的
					int cur = 0;
					vector<int> step;
					for(int k = 0; k <= i && k <= j; ++k)
						cur = tran(cur, id(g[i - k][j - k])), step.pb(cur);
					for(int k = 0; k < SZ(step) - 1 && k < T; ++k)
						if(step[k]) ret[step[k] - 1]++;// 向左上延伸的状态没到极限最多出现一次
					if(step.back())
						ret[step.back() - 1] += max(0, T - SZ(step) + 1);// 向左上延伸到极限会出现max(0, T - SZ(step) + 1)次
				}
		return ret;
    }
};
