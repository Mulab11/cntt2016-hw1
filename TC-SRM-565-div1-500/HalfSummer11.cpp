#line 2 "TheDivisionGame.cpp"
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
#define maxn 32000
#define maxm 1000010
typedef long long ll;
using namespace std;
int lim = 31700;
bool np[maxn];
int p[maxn], tot; // 不超过sqrt(upperbound)的质数
int num[maxm], rest[maxm], cnt[100]; // num[i]表示第i个数的质因子个数,rest[i]表示被质因子除得到的商,cnt[x]表示sg函数前缀和中x的出现次数
void sieve() { // 筛(多余...
	cl(np); tot = 0;
	for (int i = 2; i <= lim; ++i) {
		if (!np[i]) p[++tot] = i;
		for (int j = 1; j <= tot && p[j] * i <= lim; ++j) {
			np[p[j] * i] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
class TheDivisionGame {
	public:
		long long countWinningIntervals(int L, int R) {
			sieve(); cl(num); cl(cnt);
			for (int i = L; i <= R; ++i) rest[i - L + 1] = i;
			for (int i = 1; i <= tot; ++i) {
				int tmp = (L / p[i]) * p[i];
				while (tmp < L) tmp += p[i];
				for (; tmp <= R; tmp += p[i]) { // 将[L, R]范围内p[i]的倍数中p[i]的个数统计出来
					while (rest[tmp - L + 1] % p[i] == 0) {
						rest[tmp - L + 1] /= p[i]; ++num[tmp - L + 1];
					}
				}
			}
			for (int i = 1; i <= R - L + 1; ++i) {
				if (rest[i] > 1) ++num[i]; // 还剩下的部分,是一个大于sqrt的质数
				num[i] ^= num[i - 1]; // 前缀和
			}
			++cnt[0]; ll ans = 0;
			for (int i = 1; i <= R - L + 1; ++i) {
				ans += cnt[num[i]]; // 与它前缀和相等的位置的个数,就是可以选为左端点的位置个数
				cnt[num[i]]++;
			}
			ans = 1ll * (R - L + 1) * (R - L + 2) / 2ll - ans; // 总数 - sg值为0的区间数
			return ans;
		}
};
