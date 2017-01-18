#line 2 "TheSquareRootDilemma.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 80000
typedef long long ll;
using namespace std;
int scnt[maxn]; // scnt[i]表示小于等于i的完全平方数个数
int p[maxn], tot; // 质数
bool np[maxn]; // 是否不是质数
void sieve(int n) { // 筛质数
	cl(np); tot = 0;
	for (int i = 2; i <= n; ++i) {
		if (!np[i]) p[++tot] = i;
		for (int j = 1; j <= tot && p[j] * i <= n; ++j) {
			np[p[j] * i] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
class TheSquareRootDilemma {
	public:
		int countPairs(int n, int m) {
			int ans = 0;
			if (n < m) swap(n, m);
			sieve(n); cl(scnt);
			for (int i = 1; i * i <= n; ++i)
				++scnt[i * i];
			for (int i = 1; i <= n; ++i) scnt[i] += scnt[i - 1];
			for (int i = 1; i <= n; ++i) {
				int tmp = i, t, res = 1; // res记录出现奇数次的质数之积
				for (int j = 1; p[j] * p[j] <= tmp && j <= tot; ++j)
					if (tmp % p[j] == 0) {
						t = 0;
						while (tmp % p[j] == 0)
							tmp /= p[j], t ^= 1;
						if (t) res *= p[j]; 
					}
				if (tmp > 1) res *= tmp;
				ans += scnt[m / res]; // B中必须出现这些在A中出现奇数次的质数，余下部分需要是一个完全平方数，方案数 = m / res 以内完全平方数的个数
			}
			return ans;
		}
};
