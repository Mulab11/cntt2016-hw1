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

const int maxn = 7;
const int maxs = 17;
const int maxm = 153;
const int maxc = 5e3+115;
const int mod = 1234567891;

int C, K, total;//total为矩阵状态总数
LL H;
int tt[maxn];
int lst[maxs][maxn], cost[maxs], lt = 0;//lt为四个位置的异同情况的总数，cost为这一层有多少个面两边颜色一样
struct Matrix
{
	LL t[maxm][maxm];
	void reset()
	{
		memset(t, 0, sizeof(t));
	}
}Trans;

int Gettip(int x, int sp)//得到这种状态的编号
{
	return sp * (lt + 1) + x;
}

void Dfs(int p, int mx)//搜索四个位置的异同情况
{
	if (p == 5) {
		++lt;
		for (int i = 1; i <= 4; ++i) {
			lst[lt][i] = tt[i];
		}
		int cnt = 0;
		for (int i = 0; i < 4; ++i) {
			cnt += (tt[i + 1] == tt[(i + 1) % 4 + 1]);
		}
		cost[lt] = cnt;
		return;
	}
	for (int i = 1; i <= mx + 1; ++i) {
		tt[p] = i;
		if (i == mx + 1) Dfs(p + 1, mx + 1);
		else Dfs(p + 1, mx);
	}
}

void Match(int kind, int p, int x, int y)//搜索从一层到他上面一层的转移
{
	if (p == 5) {//这一层有kind种颜色，枚举下一层的颜色，kind+1表示任意一种这一层没出现过的颜色
		bool ever[7] = {0};
		int cnt = 0, cos = 0;
		LL X = 1;
		for (int i = 1; i <= 4; ++i) {
			if (tt[i] == kind + 1) {
				ever[lst[y][i]] = 1;
			}
		}
		for (int i = 1; i <= 4; ++i) {
			if (ever[i]) {
				++cnt;
				X = X * (C - kind - cnt + 1) % mod;//对于kind+1可以选那种颜色的计算
			}
		}
		if (cnt + kind > C) return;//颜色数不够
		for (int i = 1; i <= 4; ++i) {
			for (int j = i + 1; j <= 4; ++j) {//枚举的颜色与颜色异同情况不符合的要去掉
				if (lst[y][i] == lst[y][j] && tt[i] != tt[j]) return;
				if ((tt[i] == tt[j] && tt[i] != kind + 1) && lst[y][i] != lst[y][j]) return;
			}
		}
		for (int i = 1; i <= 4; ++i) {//两层之间有多少相邻的同色块
			cos += (tt[i] == lst[x][i]);
		}
		cos += cost[y];
		for (int i = 0; i <= K - cos; ++i) {//添加到转移矩阵中
			(Trans.t[Gettip(x, i)][Gettip(y, i + cos)] += X) %= mod;
		}
		return;
	}
	for (int i = 1; i <= kind + 1; ++i) {
		tt[p] = i;
		Match(kind, p + 1, x, y);
	}
}

void Prepare()
{
	Dfs(1, 0);//搜索颜色异同情况
	Trans.reset();
	for (int i = 1; i <= lt; ++i) {//搜索转移矩阵
		int kind = 0;
		for (int j = 1; j <= 4; ++j) Ckmax(kind, lst[i][j]);
		if (kind > C) continue;
		for (int j = 1; j <= lt; ++j) {
			Match(kind, 1, i, j);
		}
	}
	total = Gettip(lt, K);
	++total;
	for (int i = 1; i <= lt; ++i) {//使所有合法情况能累加到答案中
		for (int j = 0; j <= K; ++j) {
			Trans.t[Gettip(i, j)][total] = 1;
		}
	}
	Trans.t[total][total] = 1;//答案自己累加
}

Matrix Mult(const Matrix &a, const Matrix &b)//矩阵乘法
{
	static Matrix c;
	c.reset();
	for (int i = 0; i <= total; ++i) {
		for (int j = 0; j <= total; ++j) {
			for (int k = 0; k <= total; ++k) {
				c.t[i][j] = (c.t[i][j] + a.t[i][k] * b.t[k][j] % mod) % mod;
			}
		}
	}
	return c;
}

LL Solve()
{
	Matrix S, X;
	LL Ans = 0;
	S.reset();
	X = Trans;
	for (int i = 0; i <= total; ++i) S.t[i][i] = 1;
	while (H) {//矩阵快速幂
		if (H & 1) S = Mult(S, X);
		X = Mult(X, X);
		H >>= 1;
	}
	for (int i = 1; i <= lt; ++i) {//枚举第一层，并统计答案
		int kind = 0, cos = cost[i];
		LL sum = 1;
		for (int j = 1; j <= 4; ++j) Ckmax(kind, lst[i][j]);
		if (kind > C || cos > K) continue;
		for (int j = 1; j <= kind; ++j) sum = sum * (C - j + 1) % mod;
		Ans = (Ans + S.t[Gettip(i, cos)][total] * sum % mod) % mod;
	}
	return Ans;
}

class TheBrickTowerHardDivOne {
    public:
    int find(int _c, int _k, long long _h) {
		C = _c;
		K = _k;
		H = _h;
		lt = 0;
		Prepare();//搜出状态及转移矩阵
		return Solve();//矩阵快速幂及统计答案
    }
};


