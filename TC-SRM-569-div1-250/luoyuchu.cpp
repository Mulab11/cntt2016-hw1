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

class TheDevice {
    public:
    int minimumAdditional(vector<string> plates) {
		n = plates.size();
		m = plates[0].length();
		int cnt[2], Ans = 0;//cnt统计一位中0和1的个数
		for (int i = 0; i < m; ++i) {
			cnt[0] = cnt[1] = 0;
			for (int j = 0; j < n; ++j) {
				++cnt[plates[j][i] - '0'];
			}
			if (cnt[0] < 1 || cnt[1] < 2) {//更新差距
				Ans = max(Ans, max(0, (1 - cnt[0])) + max(0, (2 - cnt[1])));
			}
		}
        return Ans;//返回最大差距
    }
};
