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

int n;
bool mat[maxn][maxn];//输入的图
bool bao[maxn][maxn];//传递闭包
int dfn[maxn], low[maxn], Index = 0;//用于tarjan的数组
int color[maxn], cnt[maxn], sta[maxn], st = 0, ct = 0;
bool del[maxn], ever[maxn];//del表示这个点是否位于一个强联通分量，ever为二分图匹配时记录是否到过
int Lnk[maxn];//Lnk[i]为i点匹配的哪一个点

void Tarjan(int p)//Tarjan找强联通分量
{
	dfn[p] = low[p] = ++Index;
	sta[++st] = p;
	for (int i = 1; i <= n; ++i) {
		if (mat[p][i] && color[i] == 0) {
			if (dfn[i] == 0) {
				Tarjan(i);
				Ckmin(low[p], low[i]);
			}
			else {
				Ckmin(low[p], dfn[i]);
			}
		}
	}
	if (low[p] == dfn[p]) {
		++ct;
		while (sta[st] != p) {
			color[sta[st]] = ct;
			++cnt[ct];
			--st;
		}
		color[p] = ct;
		++cnt[ct];
		--st;
	}
}

void Floyd()//Floyd求传递闭包
{
	memcpy(bao, mat, sizeof(bao));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				bao[j][k] |= (bao[j][i] & bao[i][k]);
			}
		}
	}
}

int Dfs(int p)//二分图找增广轨
{
	for (int i = 1; i <= n; ++i) {
		if (del[i] || (!bao[p][i]) || ever[i]) continue;
		ever[i] = 1;
		if (Lnk[i] == 0 || Dfs(Lnk[i])) {
			Lnk[i] = p;
			return 1;
		}
	}
	return 0;
}

int Solve()
{
	int Ans = n;
	memset(dfn, 0, sizeof(dfn));//初始化
	memset(cnt, 0, sizeof(cnt));
	memset(cnt, 0, sizeof(cnt));
	memset(del, 0, sizeof(del));
	Index = 0;
	st = 0;
	ct = 0;
	for (int i = 1; i <= n; ++i) {//强联通分量一律不能选
		if (dfn[i] == 0) {
			Tarjan(1);
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (mat[i][i] || cnt[color[i]] > 1) {//自环也算强联通分量
			del[i] = 1;
			Ans -= 1;
		}
	}
	memset(Lnk, 0, sizeof(Lnk));//根据dilworth定理，将题目要求的转为求最少链覆盖，求最少链覆盖时先求传递闭包，再用二分图匹配求出最少路径覆盖
	for (int i = 1; i <= n; ++i) {
		if (!del[i]) {
			memset(ever, 0, sizeof(ever));
			Ans -= Dfs(i);
		}
	}
	return Ans;
}

class Incubator {
    public:
    int maxMagicalGirls(vector<string> love) {
		n = love.size();
		memset(mat, 0, sizeof(mat));
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				mat[i][j] = (love[i - 1][j - 1] == 'Y');
			}
		}
		Floyd();//Floyd求传递闭包
		return Solve();
    }
};


