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

const int maxn = 5e5+115;
const int maxm = 2e4+115;

int prime[maxn], pt;
bool flag[maxn];
bool ban[maxm];
int mu[maxn];
vector<int> ps[maxm];
vector<int> ys[maxm];
int lst[maxm][2], lt;

void Prepare()//预处理mu和质数
{
	const int N = 5e5;
	pt = 0;
	mu[1] = 1;
	memset(flag, 0, sizeof(flag));
	for (int i = 2; i <= N; ++i) {
		if (flag[i] == 0) {
			prime[++pt] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= pt; ++j) {
			if (i * prime[j] > N) break;
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}

int Kf(LL x, int y)//二分将x开y次方
{
	int l, r, mid;
	LL S;
	l = max(0, (int)(pow(x, 1.0 / y) - 10));
	r = (int)(pow(x, 1.0 / y) + 10);
	while (l != r) {
		mid = (l + r + 1) / 2;
		S = 1;
		for (int j = y; j > 0; --j) S = S * mid;
		if (S > x) r = mid - 1;
		else l = mid;
	}
	return l;
}

int gcd(int a, int b)//求最大公约数
{
	while (b) {
		b ^= a ^= b ^= a %= b;
	}
	return a;
}

void Getps()//预处理某个数的倍数的mu的绝对值的前缀和
{
	const int Up = 2e4;
	int N3 = Kf(8e16, 3);
	for (int i = 1; i <= Up; ++i) {
		int up_boundary = N3 / i;
		int s = 0, is = 0;
		ps[i].resize(up_boundary + 1);
		for (int j = 0; j <= up_boundary; ++j) {
			ps[i][j] = (s += abs(mu[is]));
			is += i;
		}
	}
}

void Dfs(int bel, int p, int s)//Dfs搜索出所有的约数
{
	if (p == lt + 1) {
		ys[bel].push_back(s);
		return;
	}
	Dfs(bel, p + 1, s);
	for (int i = 1; i <= lst[p][1]; ++i) {
		s *= lst[p][0];
		Dfs(bel, p + 1, s);
	}
}

void GetY()//预处理某个数的所有约数
{
	const int Up = 2e4;
	for (int i = 1; i <= Up; ++i) {
		int tmp = i;
		lt = 0;
		for (int j = 1; j <= pt && prime[j] * prime[j] <= tmp; ++j) {
			if (tmp % prime[j] == 0) {
				lst[++lt][0] = prime[j];
				lst[lt][1] = 0;
				while (tmp % prime[j] == 0) {
					tmp /= prime[j];
					++lst[lt][1];
				}
				if (lst[lt][1] >= 3) ban[i] = 1;
			}
		}
		if (tmp != 1) {
			lst[++lt][0] = tmp;
			lst[lt][1] = 1;
		}
		Dfs(i, 1, 1);
	}
}

LL Solve(LL N)//所有的符合条件的数均可以表示为形如c*d^2或a*b^3的形式
{
	LL Ans = 0;
	LL ta;
	for (int i = 1; (LL)i * i * i <= N; ++i) {//先求出所有能表示为c*d^2的数
		if (mu[i] == 0) continue;
		int Upboundary = Kf(N / i, 2);
		if (Upboundary > i) {
			Ans += Upboundary - i;
		}
	}
	//再求出所有能表示为a*b^3但不能表示为c*d^2的数
	for (int a = 1, up_a = Kf(N, 4); a <= up_a; ++a) {//枚举a
		ta = Ans;
		if (ban[a]) {
			continue;
		}
		for (int k = 1, up_k = Kf(a, 3); k <= up_k; ++k) {//k^2|ab
			int a_ = a / gcd(a, k * k), k_ = k * k / gcd(a, k * k);
			int l, r, d;
			l = a / k_ + 1;
			r = Kf(N / a, 3) / k_;
			if (mu[a_] == 0) continue;
			for (int i = ys[a_].size() - 1; i >= 0; --i) {//莫比乌斯容斥
				d = ys[a_][i];
				if (mu[d] == 0) continue;
				if (mu[d] == 1) {
					Ans += ps[d][r / d] - ps[d][(l - 1) / d];
				}
				else {
					Ans -= ps[d][r / d] - ps[d][(l - 1) / d];
				}
			}
		}
	}
	return Ans;
}

class SemiPerfectPower {
    public:
    long long count(long long L, long long R) {
		Prepare();//预处理mu和质数
		Getps();//预处理某个数的倍数的mu的绝对值前缀和
		GetY();//预处理某个数的所有约数
        return Solve(R) - Solve(L - 1);//答案为两个前缀和之差
    }
};
