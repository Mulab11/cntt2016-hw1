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
LL a[N], b[N], r;
int num[N];
int n;
/*
 * 这个题和另外一个题很像 
 * 直接xjb搞贪心就可以了
 * 可以用位运算加速
 */
class BitwiseAnd {
	public:
		vector<long long> lexSmallest(vector<long long> subset, int N) {
			n = subset.size();
			vector<LL> ans;
			vector<LL> emp;
			CL(num, 0);
			REP(i, 1, n) a[i] = subset[i - 1];
			REP(i, 1, n)
				REP(j, 0, 59) if (a[i] & (1LL << j)) ++num[j];
			REP(i, 1, n) 
				REP(j, i + 1, n) 
				if (a[i] & a[j]); else return emp;//先把一些trivial的不合法的情况给判掉
			REP(i, 0, 59) if (num[i] > 2) return emp;
			REP(i, 1, n) ans.PB(a[i]);
			REP(i, 1, n) REP(j, 0, 59) if (a[i] & (1LL << j)) 
				if (num[j] == 2) a[i] ^= (1LL << j); //记录哪些是可以用的
			r = 0; 
			REP(i, 0, 59) if (!num[i]) r |= (1LL << i);//记录哪些是不能用的
			int T = N;
			N -= n;
			int m = n;
			while (N--) {
				++n;
				REP(i, 1, m) if (!a[i]) return emp;//因为要字典序最小 所以要贪心得选择
				else {
					a[n] += lowbit(a[i]);
					a[i] -= lowbit(a[i]);
				}
				REP(i, n + 1, T) {
					if (!r) return emp;
					a[n] += lowbit(r);
					a[i] += lowbit(r);
					r -= lowbit(r);
				}
			}
			REP(i, m + 1, n) ans.PB(a[i]);
			sort(ans.begin(), ans.end());
			return ans;
		}
};

// Powered by Greed 2.0-RC
