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

const int maxn = 77777;
const int maxm = 7647;

class TheSquareRootDilemma {
    public:

	map<int, int> Counter;
	int prime[maxn + 5], pt;
	bool flag[maxn + 5];

	void Oular()//欧拉筛质数
	{
		for (int i = 2; i <= maxn; ++i) {
			if (flag[i] == 0) prime[++pt] = i;
			for (int j = 1; j <= pt; ++j) {
				if (prime[j] * i > maxn) break;
				flag[prime[j] * i] = 1;
				if (i % prime[j] == 0) break;
			}
		}
	}
	
    int countPairs(int N, int M) {
		int mask, cnt;
		int res, Ans = 0;
		Oular();
		for (int i = 1; i <= N; ++i) {
			mask = 1;//mask表示所有次数为奇数的质数的积
			res = i;
			for (int j = 1; res != 1; ++j) {
				cnt = 0;//计算每个质数的次数
				while (res % prime[j] == 0) {
					res /= prime[j];
					cnt ^= 1;
				}
				if (cnt) mask *= prime[j];
			}
			Counter[mask] += 1;//统计个数
		}
		for (int i = 1; i <= M; ++i) {
			mask = 1;
			res = i;
			for (int j = 1; res != 1; ++j) {
				cnt = 0;//计算每个质数的次数
				while (res % prime[j] == 0) {
					res /= prime[j];
					cnt ^= 1;
				}
				if (cnt) mask *= prime[j];
			}
			Ans += Counter[mask];//任意两个次数为奇数的质数的集合完全一样的数满足条件
		}
        return Ans;
    }
};

