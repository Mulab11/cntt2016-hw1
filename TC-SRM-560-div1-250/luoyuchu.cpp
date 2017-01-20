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

int n, m;
int cnt[maxn];

class TomekPhone {
    public:
    int minKeystrokes(vector<int> frequencies, vector<int> keySizes) {
		int total = 0;
		int ans = 0;
		n = keySizes.size();
		m = frequencies.size();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			total += keySizes[i];//total为可以输入的字符数
			for (int j = 1; j <= keySizes[i]; ++j) {
				++cnt[j];//cnt[i]表示输入一个需要按键i次的字符数
			}
		}
		if (m > total) return -1;//字符太多
		sort(frequencies.begin(), frequencies.end());
		--m;
		for (int i = 1; i <= 50; ++i) {
			for (int j = 1; j <= cnt[i]; ++j) {//将出现多的字符放在按键少的地方
				ans += frequencies[m] * i;
				--m;
				if (m == -1) return ans;
			}
		}
    }
};
