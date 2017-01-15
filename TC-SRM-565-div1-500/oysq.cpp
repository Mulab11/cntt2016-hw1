// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheDivisionGame.cpp"
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

const int N = 1e9;
const int SQRTN = 32000;
const int LEN = 1e6;

int p[SQRTN + 9], pn;// p[] 为质数集合
bool is[SQRTN + 9];

void sieve(int n) {// 欧拉筛法
	pn = 0;
	for(int i = 2; i <= n; ++i) {
		if(!is[i]) p[++pn] = i;
		for(int j = 1; j <= pn && p[j] * i <= n; ++j) {
			is[p[j] * i] = true;
			if(i % p[j] == 0) break;
		}
	}
}

int len;
int num[LEN + 9];
int cnt[LEN + 9];// 如果将x(L <= x <= R)表示成pi^ai的乘积，那么cnt[x - L + 1] = sigma{ai}
int pre[LEN + 9];// pre[i] = cnt[1] ^ cnt[2] ^ ... ^ cnt[i]
int c[1000];// c[i] 表示前缀中pre = i的个数

struct TheDivisionGame {
    long long countWinningIntervals(int L, int R) {
		len = R - L + 1;
		for(int i = 1; i <= len; ++i) num[i] = L + i - 1, cnt[i] = 0;
		sieve(SQRTN);
		for(int i = 1; i <= pn; ++i) {// 用 <= sqrt(n)的质数去求出每个数的cnt
			int v = p[i];
			while(v <= R) {
				for(int j = (L + v - 1) / v * v; j <= R; j += v)
					num[j - L + 1] /= p[i], cnt[j - L + 1]++;
				if((ll)v * p[i] > R) break;
				v *= p[i];
			}
		}
		for(int i = 1; i <= len; ++i)
			if(num[i] > 1) cnt[i]++;// 当剩下的数仍然 > 1时，必定是一个 > sqrt(n) 的质数
		memset(c, 0, sizeof c);
		c[0] = 1;
		ll ans = (ll)len * (len + 1) / 2;// 总方案数
		for(int i = 1; i <= len; ++i) {
			pre[i] = cnt[i] ^ pre[i - 1];
			ans -= c[pre[i]];// 根据NIM游戏的原理，减去异或值为0的区间
			c[pre[i]]++;
		}
		return ans;
    }
};
