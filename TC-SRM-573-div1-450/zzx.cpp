/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 60;
LL d[N][N]; //d[i][j] 目前在i号点 高度为j号点的高度的最小代价
bool vis[N][N];
int n;
queue<PII> q;
class SkiResorts {
	public:
		long long minCost(vector<string> g, vector<int> h) {
            n = g.size();
            REP(i, 0, n - 1) REP(j, 0, n - 1) d[i][j] = 1e18;
            REP(i, 0, n - 1) d[0][i] = abs(h[0] - h[i]), q.push(MP(0, i)), vis[0][i] = 1; // 先把0号点所有可以改到的高度全放进队列
            while (!q.empty()) {// SPFA
                int a = q.front().FR, b = q.front().SC; q.pop(); 
                vis[a][b] = 0;
                REP(i, 0, n - 1) if (g[a][i] == 'Y')
                    REP(j, 0, n - 1) if (h[j] <= h[b] && d[i][j] > d[a][b] + abs(h[i] - h[j])) {
                        d[i][j] = d[a][b] + abs(h[i] - h[j]); //每一次的代价是abs(h[i] - h[j])
                        if (!vis[i][j]) q.push(MP(i, j)), vis[i][j] = 1;
                    }
            }
            LL ans = 1e18;
            REP(i, 0, n - 1) getmin(&ans, d[n - 1][i]);//给n - 1号点找一个最优的海拔
            if (ans == 1e18) ans = -1;
			return ans;
		}
};
