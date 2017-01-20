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

int n, Len;
int ps[maxn];
int cr[maxn];
int cnt[maxn];
int dc[maxn];

class SurveillanceSystem {
    public:
    string getContainerInfo(string containers, vector<int> reports, int L) {
		string Ans;
		n = containers.length();
		Len = L;
		Ans.clear();
		memset(ps, 0, sizeof(ps));
		memset(cr, 0, sizeof(cr));
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; ++i) {
			ps[i] = ps[i - 1] + (containers[i - 1] == 'X');//前缀和
		}
		for (int i = 0; i < (int)reports.size(); ++i) {//总计reports中不同数字的个数
			++cr[reports[i]];
		}
		for (int i = 1; i + Len - 1 <= n; ++i) {//统计所有可能的位置的数字的个数
			++cnt[ps[i + Len - 1] - ps[i - 1]];
		}
		for (int i = 1; i <= n; ++i) {
			bool za = 0, bz = 1;
			memset(dc, 0, sizeof(dc));
			for (int j = max(1, i - Len + 1); j <= min(n - Len + 1, i); ++j) {//统计如果这个点不被覆盖，不能选择的数字的个数
				++dc[ps[j + Len - 1] - ps[j - 1]];
			}
			for (int j = 0; j <= Len; ++j) {//如果不覆盖就不能达到，则必须选
				if (cnt[j] - dc[j] < cr[j]) {
					za = 1;
				}
			}
			for (int j = 0; j <= Len; ++j) {//不过选择这个点，就一定会多出一个不存在的数字，则不能选
				if (dc[j] > 0 && cr[j] > 0) {
					bz = 0;
					break;
				}
			}
			if (za) Ans += '+';
			else if (bz) Ans += '-';
			else Ans += '?';
		}
        return Ans;//返回答案
    }
};

