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

const int maxn = 1e6+15;
const int maxm = 2e5+15;

LL N, Mp, Ans;
int prime[maxn], pt = 0, lt = 0;
bool flag[maxn] = {0};
LL lst[maxm];//N/x的所有商
int dy[maxm];
LL f[maxm], g[maxm];//f[i]表示所有数x，使得N/x向下取整等于i的数中当前能被组合出来的数有多少个，g[i]是f[i]的滚动数组

int Gettip(LL x)//二分查找x的下标
{
	register int l, r, mid;
	l = 1, r = lt;
	while (l != r) {
		mid = (l + r) >> 1;
		if (lst[mid] == x) return mid;
		else if (lst[mid] < x) r = mid;
		else l = mid + 1;
	}
	return l;
}

int Findprime(LL x)//二分查找比x小的质数
{
	register int l, r, mid;
	l = 1, r = pt;
	if (x == 1) return 0;
	while (l != r) {
		mid = (l + r + 1) / 2;
		if (prime[mid] <= x) l = mid;
		else r = mid - 1;
	}
	return l;
}

void Prepare()
{
	pt = 0;
	memset(flag, 0, sizeof(flag));
	for (int i = 2; i <= Mp; ++i) {//欧拉筛质数
		if (flag[i] == 0) {
			prime[++pt] = i;
		}
		for (int j = 1; j <= pt; ++j) {
			if (i * prime[j] > Mp) break;
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
	//dig("%d\n", pt);
	lt = 0;
	for (LL i = 1; i <= N; i = N / (N / i) + 1) {//预处理N/x的根号N种结果
		lst[++lt] = N / i;
		dy[lt] = Findprime(lst[lt]);
	}
	/*
	dig("%d\n", lt);
	for (int i = 1; i <= lt; ++i) {
		dig("%lld ", lst[i]);
	}
	dig("\n");
	*/
}

void Solve()
{
	register int last = lt, t;
	register LL p2, p1;
	memset(f, 0, sizeof(f));
	f[1] = 1;
	for (int i = 1; i <= pt && prime[i] <= Mp; ++i) {//背包Dp
		p2 = (LL)prime[i] * prime[i];//p的平方
		p1 = prime[i];//p
		while (last > 0 && lst[last] < p2) {//对于所有N/x小于p的平方的数，由于质数是从小到大考虑，所以一定只能至多放一个质数，可以直接统计
			if (dy[last] >= i) Ans += f[last] * (dy[last] - i + 1);
			Ans += f[last];
			--last;
		}
		if (last == 0) break;
		for (int j = 1; j <= last; ++j) g[j] = 0;//清空
		for (int j = 1; j <= last; ++j) {//由于题目要求是质数的奇数次幂，所以先放1个，然后再两个两个放
			t = Gettip(lst[j] / p1);
			if (t > last) {//中途有超出来的数直接统计答案
				if (dy[t] > i) {
					Ans += (dy[t] - i) * f[j];
				}
				Ans += f[j];
			}
			else {
				g[t] += f[j];
			}
		}
		for (int j = 1; j <= last; ++j) {//质数的平方做无限背包
			t = Gettip(lst[j] / p2);
			if (t > last) {
				if (dy[t] > i) {
					Ans += (dy[t] - i) * g[j];
				}
				Ans += g[j];
			}
			else {
				g[t] += g[j];
			}
		}
		for (int j = 1; j <= last; ++j) f[j] += g[j];
	}
	for (int i = 1; i <= last; ++i) {
		Ans += f[i];
	}
}

class HolyNumbers {
    public:
    long long count(long long upTo, int maximalPrime) {
		Ans = 0;
		N = upTo;
		Mp = maximalPrime;
		if (Mp == 1) return min(1LL, upTo);
		Prepare();//预处理质数，商
		Solve();//背包Dp
        return Ans;
    }
};
