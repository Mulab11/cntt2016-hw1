#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 1e6+115;
const int maxm = 4e4+115;

int n;
int res[maxn], cnt[maxn];//res表示这个数除去已经计算的cnt个质因数，还剩下多少
int ge[maxm];//ge[i]表示i这个数有多少个质因数
map<int, int> Hash;//Hash[i]表示在之前的前缀和中等于i的有多少个

void Prepare(int L, int R)
{
	int s = 0, tmp;
	for (int i = 1; i < maxm; ++i) {//预处理小范围内每个数的质因数个数
		s = 0;
		tmp = i;
		for (int j = 2; j * j <= tmp; ++j) {
			while (tmp % j == 0) {
				++s;
				tmp /= j;
			}
		}
		if (tmp != 1) ++s;
		ge[i] = s;
	}
	for (int i = 1; i <= n; ++i) res[i] = L + i - 1, cnt[i] = 0;//初始化
	for (int i = maxm - 1; i >= 2; --i) {//对于每个数分解质因数
		for (int st = (L - 1) / i * i + i; st <= R; st += i) {
			while (res[st - L + 1] % i == 0) {
				res[st - L + 1] /= i;
				cnt[st - L + 1] += ge[i];
			}
		}
	}
	for (int i = 1; i <= n; ++i) {//可能剩余一个大于sqrt(x)的质数
		if (res[i] != 1) {
			++cnt[i];
		}
	}
}

LL Solve()
{
	LL Ans = 0;
	Hash.clear();
	cnt[0] = 0;
	for (int i = 1; i <= n; ++i) {//求前缀和
		cnt[i] ^= cnt[i - 1];
	}
	Hash[cnt[0]] += 1;
	for (int i = 1; i <= n; ++i) {//所有异或为0的区间都是先手必败的
		Ans += Hash[cnt[i]];
		Hash[cnt[i]] += 1;
	}
	return (LL)(n + 1) * n / 2 - Ans;//总数减去先手必败
}

class TheDivisionGame {
    public:
    long long countWinningIntervals(int L, int R) {
		n = R - L + 1;
		Prepare(L, R);
		return Solve();
    }
};

