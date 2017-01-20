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

const int maxn = 51;
const int mod = 1e9+7;

int n;
int jc[maxn];
map<int, int> f[maxn][maxn][maxn];

int Dp(int p, int emp, int up, int nd)//表示当前已经确定了n~p的数的位置，A，B序列有emp个公共位置都没有确定，只有B序列确定的位置有up个，只有A序列确定的位置有down个，现在的magic和距离目标还有nd
{
	if (nd <= 0) return jc[p];//已经超过或等于k，之后可以乱放
	if (p == 0) return 0;//达不到k
	if (f[p][emp][up].count(nd)) return f[p][emp][up][nd];
	int down = n * 2 - emp * 2 - up - (n - p) * 2;
	int s = 0;//由于从小到达放置数，所以只有在将数放入一个A，B序列都是空的位置的时候才增加magic值
	if (up > 0 && down > 0) {
		(s += (LL)Dp(p - 1, emp, up - 1, nd) * up * down % mod) %= mod;
	}
	if (up > 0 && emp > 0) {
		(s += (LL)Dp(p - 1, emp - 1, up, nd - p) * up * emp % mod) %= mod;
	}
	if (down > 0 && emp > 0) {
		(s += (LL)Dp(p - 1, emp - 1, up, nd - p) * down * emp % mod) %= mod;
	}
	if (emp > 1) {
		(s += (LL)Dp(p - 1, emp - 2, up + 1, nd - p - p) * emp * (emp - 1) % mod) %= mod;
	}
	if (emp > 0) {
		(s += (LL)Dp(p - 1, emp - 1, up, nd - p) * emp % mod) %= mod;
	}
	return f[p][emp][up][nd] = s;
}

class LittleElephantAndPermutationDiv1 {
    public:
    int getNumber(int N, int K) {
		n = N;
		jc[0] = 1;
		for (int i = 1; i <= n; ++i) {//预处理阶乘的平方
			jc[i] = (LL)jc[i - 1] * i % mod;
		}
		for (int i = 0; i <= n; ++i) {
			jc[i] = (LL)jc[i] * jc[i] % mod;
		}
        return Dp(n, n, 0, K);//记忆化搜索
    }
};
