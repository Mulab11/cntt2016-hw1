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

class BinPacking {
    public:
    int minBins(vector<int> item) {
		vector<int> sieve;
		int n = item.size();
		int cnt = 0, ans = 2e9;
		sieve.clear();
		for (int i = 0; i < n; ++i) {
			if (item[i] == 100) {
				++cnt;
			}
			else {
				sieve.push_back(item[i]);
			}
		}
		int sum = 0;
		for (int i = 1; i <= cnt % 3; ++i) sieve.push_back(100);//只有3个100的情况下能够1个箱子装3个，否则为1～2的
		for (int k = cnt / 3; k >= 0; --k) {//枚举将多少个100的物品放在装3个的箱子里
			sum = k;
			sort(sieve.begin(), sieve.end());
			for (int i = sieve.size() - 1, j = 0; i >= j; --i) {//其余物品贪心放置即可
				if (sieve[i] + sieve[j] <= 300) {
					++j;
				}
				++sum;
			}
			Ckmin(ans, sum);
			for (int i = 0; i < 3; ++i) sieve.push_back(100);
		}
        return ans;
    }
};
