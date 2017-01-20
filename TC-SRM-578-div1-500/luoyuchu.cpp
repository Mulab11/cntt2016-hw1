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

const int maxn = 315;
const int mod = 1e9+7;

int n, m;
int L[maxn], R[maxn];
pair<int, int> interval[maxn];

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return (a.first < b.first || (a.first == b.first && a.second > b.second));
}

int Init(vector<string> a, int b[])//输入
{
	int tmp = 0;
	int total = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		for (int j = 0; j < (int)a[i].length(); ++j) {
			if (a[i][j] == ' ') {
				b[++total] = tmp;
				tmp = 0;
			}
			else {
				tmp = tmp * 10 + a[i][j] - '0';
			}
		}
	}
	b[++total] = tmp;
	return total;
}

LL Pow(LL x, int y)//快速幂
{
	LL S = 1;
	while (y) {
		if (y & 1) S = S * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return S;
}

int Dp(int l, int r)
{
	static int f[maxn][maxn];//f[i][j]表示前两条狼的位置分别为i和j的方案数
	int Ans = 0;
	int st = interval[l].first - 1;
	int N = interval[r].second - st;
	for (int i = l; i <= r; ++i) {
		interval[i].first -= st;
		interval[i].second -= st;
	}
	for (int i = 0; i <= N; ++i) {
		memset(f[i], 0, sizeof(int) * (N + 3));
	}
	f[0][0] = 1;
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (f[i][j] == 0) continue;
			(Ans += f[i][j]) %= mod;
			int p;
			for (int k = l; k <= r; ++k) {
				if (interval[k].first > j) {
					p = k - 1;
					break;
				}
			}
			if (interval[r].first <= j) p = r;//考虑是否有条件因为放满了两条狼需要跳过
			if (p < l) {
				for (int k = i + 1; k <= N; ++k) {//枚举下一条狼的位置
					(f[k][i] += f[i][j]) %= mod;
				}
			}
			else {
				for (int k = max(interval[p].second + 1, i + 1); k <= N; ++k) {
					(f[k][i] += f[i][j]) %= mod;
				}
			}
		}
	}
	return Ans;
}

int Solve()
{
	int Ans = 1;
	for (int i = 1; i <= m; ++i) {
		interval[i] = make_pair(L[i], R[i]);
	}
	sort(interval + 1, interval + 1 + m, cmp);
	int lastest = -1;
	int det = 0;
	for (int i = 1; i <= m; ++i) {//先将所有被另一个条件完全包含的条件全部删除
		if (interval[i].second <= lastest) {
			interval[i].first = 2e9;
			++det;
		}
		else {
			lastest = interval[i].second;
		}
	}
	sort(interval + 1, interval + 1 + m);//将剩下的条件排序
	m -= det;
	int last = -1, S, T;
	S = 1;
	while (S <= m) {
		Ans = Ans * Pow(2, interval[S].first - last - 1) % mod;//对于没有被任何条件约束的区间，世界乘以2^len
		T = S;
		while (T < m && interval[T + 1].first <= interval[T].second) ++T;//一次处理一段连续的有交的条件
		last = interval[T].second;
		Ans = (LL)Ans * Dp(S, T) % mod;
		S = T + 1;
	}
	Ans = Ans * Pow(2, n - last - 1) % mod;//最后一段剩余的区间
	return Ans;//返回答案
}

class WolfInZooDivOne {
    public:
    int count(int N, vector<string> L_str, vector<string> R_str) {
		n = N;
		m = Init(L_str, L);//将字符串转化为数字
		Init(R_str, R);
		return Solve();//动态规划解决问题
    }
};
