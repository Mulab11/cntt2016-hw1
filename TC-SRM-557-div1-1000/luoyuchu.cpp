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

const int maxn = 55;

int n;
LL num[maxn];
bool sel[maxn];

void Gauss()//高斯消元求出线性基
{
	memset(sel, 0, sizeof(sel));
	for (int i = 50; i >= 0; --i) {
		for (int j = 1; j <= n; ++j) {
			if (sel[j] == 0 && ((num[j] >> i) & 1)) {
				sel[j] = 1;
				for (int k = j + 1; k <= n; ++k) {
					if (sel[k] == 0 && ((num[k] >> i) & 1)) {
						num[k] ^= num[j];
					}
				}
				break;
			}
		}
	}
	sort(num + 1, num + 1 + n);
	reverse(num + 1, num + 1 + n);
	for (int i = n; i >= 1; --i) {
		int key = -1;
		for (int j = 50; j >= 0; --j) {
			if ((num[i] >> j) & 1) {
				key = j;
				break;
			}
		}
		if (key == -1) continue;
		for (int j = 1; j < i; ++j) {
			if ((num[j] >> key) & 1) {
				num[j] ^= num[i];
			}
		}
	}
	for (int i = n; i >= 1; --i) {//之后可以使得最大总和为(最大异或和*n-(去除最大的线性基的线性基之和))
		if ((num[1] ^ num[i]) > num[1]) {
			num[1] ^= num[i];
		}
	}
	for (int i = 2; i <= n; ++i) {
		num[i] ^= num[1];
	}
}

LL Solve()
{
	LL Ans = 0;
	Gauss();
	for (int i = 1; i <= n; ++i) {//统计答案
		Ans += num[i];
	}
	return Ans;
}

class XorAndSum {
    public:
    long long maxSum(vector<long long> number) {
		n = number.size();
		for (int i = 1; i <= n; ++i) {
			num[i] = number[i - 1];
		}
		return Solve();
    }
};

