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
int girls[maxn];
pair<int, LL> enemy[maxn];

bool Check(LL x)
{
	static pair<int, LL> E[maxn];
	int p = 1;
	memcpy(E, enemy, sizeof(E));//贪心判断是否有解
	for (int i = 1; i <= n; ++i) {
		LL res = x;
		while (p <= m) {
			if (E[p].first <= girls[i]) {
				if (E[p].second <= res) {
					res -= E[p].second;
					++p;
				}
				else {
					E[p].second -= res;
					res = 0;
					break;
				}
			}
			else {
				break;
			}
		}
	}
	return (p > m);
}

class SpaceWarDiv1 {
    public:
    long long minimalFatigue(vector<int> magicalGirlStrength, vector<int> enemyStrength, vector<long long> enemyCount) {
		n = magicalGirlStrength.size();
		m = enemyStrength.size();
		for (int i = 1; i <= n; ++i) girls[i] = magicalGirlStrength[i - 1];//将敌人与膜法少女按照能力排序
		sort(girls + 1, girls + 1 + n);
		for (int i = 1; i <= m; ++i) {
			enemy[i] = make_pair(enemyStrength[i - 1], enemyCount[i - 1]);
		}
		sort(enemy + 1, enemy + 1 + m);
		if (enemy[m].first > girls[n]) return -1;
		LL l = 0, r = 1e17, mid;//二分求解
		while (l != r) {
			mid = (l + r) / 2;
			if (Check(mid)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
        return l;
    }
};

