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
const int maxm = 23;

int Ys[maxm][2];
vector<int> lb[maxm];
int yt = 0;

LL Pow(LL x, int y, int mod)
{
	LL S = 1;
	while (y) {
		if (y & 1) S = S * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return S;
}

vector<int> Calc(int p, int c)
{
	static int cnt[maxn];
	static int pc[maxn];
	static vector<int> Lb;
	static bool del[maxn];
	int total = 1;
	for (int i = 1; i <= c; ++i) total *= p;
	Lb.clear();
	Lb.resize(total, 1e9);
	memset(cnt, 0, sizeof(int) * (total));
	memset(del, 0, sizeof(bool) * (total));
	pc[1] = 0; pc[0] = c;
	for (int i = 2; i < total; ++i) {//预处理每个数中包含多少个因数p
		if (i % p == 0) {
			pc[i] = pc[i / p] + 1;
		}
		else {
			pc[i] = 0;
		}
	}
	for (int i = 0; i < total; ++i) {//暴力算出随着K^2的K的增大，那些f(x+kp^c)中会包含大于等于c个p
		int k2 = (LL)i * i % p;
		int K2 = (LL)i * i % total;
		bool did = 0;
		if (del[k2]) continue;
		for (int j = 0; j + k2 < total; j += p) {//由于做一次至少增加1，所以不会超时
			if (cnt[j + k2] >= c) continue;
			did = 1;
			cnt[j + k2] += pc[(j + k2 - K2 + total) % total];
			if (cnt[j + k2] >= c) {
				Lb[j + k2] = i;
			}
		}
		if (did == 0) del[k2] = 1;
	}
	return Lb;
}

void Prepare(int d)
{
	int tmp = d;
	yt = 0;
	for (int i = 2; i * i <= tmp; ++i) {
		if (tmp % i == 0) {
			++yt;
			Ys[yt][0] = i;
			Ys[yt][1] = 0;
			while (tmp % i == 0) {
				++Ys[yt][1];
				tmp /= i;
			}
		}
	}
	if (tmp != 1) {
		++yt;
		Ys[yt][0] = tmp;
		Ys[yt][1] = 1;
	}
	for (int i = 1; i <= yt; ++i) {//如果f(x)满足，则f(x+d)一定满足，所以我们求出每个f(x+kd)满足要求的的最小k
		lb[i] = Calc(Ys[i][0], Ys[i][1]);
	}
	for (int i = 1; i <= yt; ++i) {
		Ys[i][0] = Pow(Ys[i][0], Ys[i][1], 1e9+7);
	}
}

LL Solve(LL x, int d)
{
	LL Ans = 0;
	int b;
	LL b2, L, R;
	for (int i = 0; i < d; ++i) {//已经求出不同的x的下界，直接统计答案即可
		b = 0;
		for (int j = 1; j <= yt; ++j) {
			Ckmax(b, (int)lb[j][i % Ys[j][0]]);
		}
		b2 = (LL)b * b;
		if (b2 >= x) continue;
		L = (b2 - i + d) / d;
		R = (x - i + d) / d - 1;
		if (R >= L) Ans += R - L + 1;
	}
	return Ans;
}

class SparseFactorial {
    public:
    long long getCount(long long lo, long long hi, long long divisor) {
		Prepare(divisor);//将divisor拆为质数幂分开处理
        return Solve(hi, divisor) - Solve(lo - 1, divisor);
    }
};
