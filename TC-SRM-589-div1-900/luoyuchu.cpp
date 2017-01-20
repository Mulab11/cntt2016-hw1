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

const int maxn = 355;
const int maxm = 21;

int n, m;
int str[maxn];

int Solve0()//当周期很小
{
	int N = (1 << m);
	int bn = ((n - 1) / m) + 1;
	int cr[maxm], st, tmp;
	int ans = 2e9;
	static int val[maxn][2];
	static int f[maxn][2];
	for (int i = 0; i < N; ++i) {//枚举周期
		tmp = i;
		for (int j = 1; j <= m; ++j) {
			cr[j] = tmp & 1;
			tmp >>= 1;
		}
		memset(val, 0, sizeof(val));
		for (int j = 1; j <= bn; ++j) {
			st = (j - 1) * m;
			for (int k = 1; k <= m && k + st <= n; ++k) {
				val[j][0] += (cr[k] != str[k + st]);
			}
			val[j][1] = m - val[j][0];
		}
		memset(f, 0x3f, sizeof(f));
		f[1][0] = val[1][0];
		f[1][1] = val[1][1];
		for (int j = 1; j < bn; ++j) {//Dp求出每个周期是否反转
			for (int k = 0; k < 2; ++k) {
				for (int q = 0; q < 2; ++q) {
					Ckmin(f[j + 1][q], f[j][k] + val[j + 1][q] + (k != q));
				}
			}
		}
		Ckmin(ans, f[bn][0]);
		Ckmin(ans, f[bn][1]);
	}
	return ans;
}

int Solve1()//周期数很少
{
	int bn = ((n - 1) / m) + 1, rbn = (n / m);
	int N = (1 << (bn - (n % m == 0)));
	int tmp, cr[maxm] = {0}, ans = 2e9;
	int sum = 0, cnt[2];
	int last = 0;
	for (int i = 0; i < N; ++i) {//，枚举每个周期是否去反
		tmp = i;
		last = -1;
		sum = 0;
		for (int j = 1; j <= rbn; ++j) {
			cr[j] = tmp & 1;
			sum += (tmp & 1);
			tmp >>= 1;
		}
		int s = 0;
		for (int j = bn; j >= 1; --j) {
			s += cr[j];
			cr[j] = (s & 1);
		}
		for (int j = 1; j <= m; ++j) {//贪心周期中每一位
			cnt[0] = cnt[1] = 0;
			for (int k = 0, q = 1; k + j <= n; k += m, ++q) {
				++cnt[str[k + j] ^ cr[q]];
			}
			sum += min(cnt[0], cnt[1]);
		}
		Ckmin(ans, sum);
	}
	return ans;
}

class FlippingBitsDiv1 {
    public:
    int getmin(vector<string> S, int M) {
		n = 0;
		m = M;
		for (int i = 0; i < (int)S.size(); ++i) {//由于如果要是前N-M个等同于后N-M个，所以这个字符串要变为周期为M的周期串
			for (int j = 0; j < (int)S[i].length(); ++j) {
				str[++n] = S[i][j] - '0';
			}
		}
		if (m <= 17) {//如果每个周期的长度x很小，直接枚举每个周期，然后Dp求出是否反转
			return Solve0();
		}
		else {//否则可以枚举每个周期是否反转，然后按位贪心
			return Solve1();
		}
    }
};
