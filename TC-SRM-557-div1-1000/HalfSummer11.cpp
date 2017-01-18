#line 2 "XorAndSum.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
ll b[maxn]; // 存线性基，b[i]存最高位为i的基
int n;
class XorAndSum {
	public:
		long long maxSum(vector<long long> a) {
			n = a.size();
			cl(b);
			for (int i = 0; i < n; ++i) {
				for (int j = 50; j >= 0; --j)
					if (a[i] & (1ll << ll(j))) { // 从高到低枚举为1的位
						if (b[j]) {
							a[i] ^= b[j]; // 若该位已经有基，消去这一位
						} else {
							b[j] = a[i]; // 否则，它成为这一位的线性基
							break;
						}
					}
			}
			for (int i = 0; i <= 50; ++i)
				for (int j = i + 1; j <= 50; ++j)
					if (b[i] && (b[j] & (1ll << ll(i))))
						b[j] ^= b[i]; // 消成每列至多一个1的情况
			ll mx = 0; int empty = n; // mx存用所有数能xor出的最大值，empty存被消成0了的数的个数
			for (int i = 0; i <= 50; ++i)
				if (b[i]) {
					--empty; mx ^= b[i]; // 所有的基xor起来，就得到了用这些数能够xor出的最大值。
				}
			ll ans = mx * empty; bool flag = 1; // 对于被消成0的数，依次xor上所有的基，就能得到最大值mx，它们对答案的贡献就是mx * empty
			for (int i = 50; i >= 0; --i) // 对于基，最优的办法是，先把所有基都xor到最大的基上，再用最大的基去xor每个基
				if (b[i]) {
					if (flag) {
						ans += mx; flag = 0; // 如果是最大的基，对答案的贡献是mx
					} else {
						ans += (mx ^ b[i]); // 否则，贡献是mx ^ 自己
					}
				}
			return ans;
		}
};
