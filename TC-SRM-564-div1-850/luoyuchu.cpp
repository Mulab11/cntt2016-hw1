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
const int mod = 1e9+7;

int n, aim, Ans;
int A[maxn];

int upbit(int x)//计算x在2进制下最高位的1在哪一位
{
	int cnt = -1;
	while (x) {
		x >>= 1;
		++cnt;
	}
	return cnt;
}

void Solve()
{
	int high;
	static int f[maxn][2];
	sort(A + 1, A + 1 + n);
	reverse(A + 1, A + 1 + n);
	while (n > 0 && A[n] == 0) --n;//将card[i]为0的去掉
	if (n == 0) {//特判n=0的情况
		if (aim == 0) Ans = 1;
		else Ans = 0;
		return;
	}
	while (1) {
		sort(A + 1, A + 1 + n);
		if (upbit(aim) > upbit(A[n])) break;//不可能达到目标
		high = upbit(A[n]);//每次枚举最大的card的最高位选不选
		memset(f, 0, sizeof(f));
		f[0][0] = 1;//f[i][0-1]表示前i个数，且当前最高位是0/1的选择方案数
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j <= (A[i] >> high); ++j) {
				for (int k = 0; k < 2; ++k) {
					if (j == 0) {
						f[i][j ^ k] = (f[i][j ^ k] + (LL)f[i - 1][k] * min(A[i] + 1, (1 << high)) % mod) % mod;
					}
					else {
						f[i][j ^ k] = (f[i][j ^ k] + (LL)f[i - 1][k] * (A[i] - (1 << high) + 1) % mod) % mod;
					}
				}
			}
		}
		Ans = (Ans + f[n - 1][upbit(aim) == high]) % mod;//如果A[n]的最高位不选，那么前n-1个数的除最高位的异或和总能找到唯一一个A[n]使得满足要求
		A[n] -= (1 << high);//如果最高位选，那么card[n]和aim同时异或最高位，进入一个子问题
		aim ^= (1 << high);
		if (A[n] == 0) --n;
		if (n == 0) {//递归终点
			if (aim == 0) Ans = (Ans + 1) % mod;
			break;
		}
	}
}

class DefectiveAddition {
    public:
    int count(vector<int> _c, int _a) {
		n = _c.size();
		aim = _a;
		Ans = 0;
		for (int i = 0; i < n; ++i) {
			A[i + 1] = _c[i];
		}
		Solve();
        return Ans;
    }
};

