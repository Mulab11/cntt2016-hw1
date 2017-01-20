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

const int maxn = 15;
const int maxp = 1e5+115;
const int mod = 1e9+9;

int n, m, Len, X0, Y0;
char mat[maxn][maxn];
char ml[maxn * maxn];
int Ans;
map<int, bool> Hsh;
int prime[maxp], pt;
bool flag[maxp];
LL ys[maxn][2];
int y_cnt = 0;

void Prepare()//筛质数
{
	const int N = 1e5;
	pt = 0;
	memset(flag, 0, sizeof(flag));
	for (int i = 2; i <= N; ++i) {
		if (flag[i] == 0) {
			prime[++pt] = i;
		}
		for (int j = 1; j <= pt; ++j) {
			if (i * prime[j] > N) break;
			flag[i * prime[j]] = 1;
			if (i % prime[j] == 0) break;
		}
	}
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

LL Getpos(int p)//求出子矩阵中的位置对应的大矩阵中的位置
{
	return (p / m + X0) * (LL)Len + (p % m + Y0) + 1;
}

void Check(int s)//对于一个特定的长度，计算正确的答案，并替换等比数列中的那一项
{
	static bool del[maxn * maxn];
	LL x, y;
	int cnt = 0;
	memset(del, 0, sizeof(del));
	for (int i = 0; i < n * m; ++i) {
		x = Getpos(i);
		if (del[i]) continue;
		for (int j = i + 1; j < n * m; ++j) {
			y = Getpos(j);
			if ((y - x) % s == 0) {
				del[i] = del[j] = 1;
				if (ml[i] == ml[j]) {
					++cnt;
				}
				else {
					cnt = -1;
					break;
				}
			}
		}
		if (cnt == -1) break;
	}
	if (s >= n * m) {
		Ans = (Ans - Pow(26, s - n * m) + mod) % mod;
	}
	if (cnt != -1) {
		if (s >= n * m - cnt) {
			Ans = (Ans + Pow(26, s - n * m + cnt)) % mod;
		}
	}
}

void Dfs(int p, LL s)//Dfs枚举约数
{
	if (s > Len) return;
	if (p == y_cnt + 1) {
		if (Hsh.count(s)) return;
		Hsh[s] = 1;
		Check(s);
		return;
	}
	Dfs(p + 1, s);
	for (int i = 1; i <= ys[p][1]; ++i) {
		s *= ys[p][0];
		Dfs(p + 1, s);
	}
}

void Solve()
{
	LL x, y, tmp;
	Hsh.clear();
	for (int i = 0; i < n * m; ++i) {
		x = Getpos(i);
		for (int j = i + 1; j < n * m; ++j) {//枚举给出矩阵中哪两个位置会在字符串中重合
			y = Getpos(j);
			y_cnt = 0;
			tmp = y - x;
			for (int k = 1; k <= pt && (LL)prime[k] * prime[k] <= tmp; ++k) {//字符串的长度一定是这两个位置的距离的约数，先将这个距离质因数分解
				if (tmp % prime[k] == 0) {
					ys[++y_cnt][0] = prime[k];
					ys[y_cnt][1] = 0;
					while (tmp % prime[k] == 0) {
						++ys[y_cnt][1];
						tmp /= prime[k];
					}
				}
			}
			if (tmp != 1) ys[++y_cnt][0] = tmp, ys[y_cnt][1] = 1;
			Dfs(1, 1);//Dfs枚举约数
		}
	}
}

class CharacterBoard {
    public:
    int countGenerators(vector<string> fragment, int W, int i0, int j0) {
		n = fragment.size();
		m = fragment[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i][j] = fragment[i][j];
				ml[i * m + j] = fragment[i][j];
			}
		}
		Len = W;
		X0 = i0;
		Y0 = j0;
		Prepare();//预处理出质数
		if (W < n * m) Ans = 0;
		else Ans = (1 - Pow(26, W - (n * m) + 1) + mod) % mod * Pow(mod - 25, mod - 2) % mod;//先假设给出的矩阵中的位置都只在一个串中出现一次，则用等比数列求和求出
		Solve();//处理上述情况之外的情况
        return Ans;
    }
};
 
