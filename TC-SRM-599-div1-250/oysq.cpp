// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigFatInteger.cpp"
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

const int MAX = 1e6;

struct BigFatInteger {
    int minOperations(int A, int B) {
		static int cnt[MAX + 9];// cnt[i]表示A^B质因数分解后i的次数
		// 质因数分解
		memset(cnt, 0, sizeof cnt);
		for(int i = 2; i <= A; ++i)
			while(A % i == 0) cnt[i]++, A /= i;
		std::vector<int> a;
		for(int i = 1; i <= MAX; ++i)
			if(cnt[i]) a.pb(cnt[i] * B);
		int ans = 0;
		for(auto v : a) {// 每一个质数都是独立的，取最大值
			int cur = 0;
			for(int i = v; i > 1; i = (i + 1) >> 1)// 显然二分是最优的
				cur++;
			chkmax(ans, cur);
		}
		ans += SZ(a);// 操作1的个数
		return ans;
    }
};
