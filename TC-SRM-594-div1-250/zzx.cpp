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
const int N = 100;
int a[N], b[N];
int n, m;
bool check(int a, int b, int c, int d) { // a / b = c / d
	return 1LL * a * d == 1LL * b * c;
}

int dp() {
	static int f[N][N];
	CL(f, 0);
	int ans = 0;
	REP(i, 1 , n) 
		REP(j, 1, m)  {
			f[i][j] = 1;
			REP(k1, 1, i - 1)
				REP(k2, 1, j - 1) if (check(a[k1], a[i], b[k2], b[j])) {
					getmax(&f[i][j], f[k1][k2] + 1);
				}
			getmax(&ans, f[i][j]);
		}
	return n + m - ans;
}
class AstronomicalRecords {
	public:
		int minimalPlanets(vector<int> A, vector<int> B) {
			n = A.size(), m = B.size();
			REP(i, 1, n) a[i] = A[i - 1];
			REP(i, 1, m) b[i] = B[i - 1];
			return dp();
		}
};

// Powered by Greed 2.0-RC
