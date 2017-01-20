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

const int maxn = 15;

int n, m;
int mat[maxn][maxn];
int ma[maxn][maxn];
int g[3][5][2], gt[3];
bool place[maxn];
int type[maxn];
			
void Prepare()
{
	gt[1] = 4;
	gt[2] = 5;
	g[1][0][0] = g[1][1][1] = 1;
	g[1][2][0] = g[1][3][1] = -1;
	memcpy(g[2], g[1], sizeof(g[1]));
}

void Color(int x, int y, int t)
{
	int tx, ty;
	for (int i = 0; i < gt[t]; ++i) {
		tx = x + g[t][i][0];
		ty = y + g[t][i][1];
		if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
			ma[tx][ty] ^= 1;
		}
	}
}

int Do()//模拟之后的放法
{
	int ans = 0;
	memcpy(ma, mat, sizeof(ma));
	for (int i = 0; i < n; ++i) {
		if (place[i]) {
			Color(i, 0, type[i]);
			++ans;
		}
	}
	for (int i = 1; i < m; ++i) {
		bool c[3] = {0};
		for (int j = 0; j < n; ++j) {
			if (ma[j][i - 1] == 0) {
				Color(j, i, type[j]);
				++ans;
				c[type[j]] |= 1;
			}
		}
		if (c[1] && c[2]) {//发生冲突
			return 2e9;
		}
	}
	for (int i = 0; i < n; ++i) {//最后一列不能满足
		if (ma[i][m - 1] == 0) {
			return 2e9;
		}
	}
	return ans;
}

int Solve()
{
	int N1, N2, Ans = 2e9;
	int tmp, cnt;
	N1 = (1 << n);
	for (int i = 0; i < N1; ++i) {//枚举第一列那些地方放置一个图形，再枚举统一放哪一种图形
		tmp = i;
		cnt = 0;
		for (int j = 0; j < n; ++j) {
			place[j] = (tmp & 1);
			cnt += (tmp & 1);
			tmp >>= 1;
		}
		N2 = (1 << (n - cnt));
		for (int j = 0; j < N2; ++j) {//枚举每一行如果要放置图形，应该统一是哪一种类型
			tmp = j;
			for (int k = 0; k < n; ++k) {
				if (place[k] == 0) {
					type[k] = ((tmp & 1) ? 1 : 2);
					tmp >>= 1;
				}
			}
			for (int k = 1; k <= 2; ++k) {
				for (int q = 0; q < n; ++q) {
					if (place[q] == 1) {
						type[q] = k;
					}
				}
				Ckmin(Ans, Do());//由于第一列确定，以及每一行的图形种类确定就能确定后面所有的信息，所以只需模拟然后更新答案即可
			}
		}
	}
	if (Ans > 1e9) return -1;
	else return Ans;//返回答案
}

class YetAnotherBoardGame {
    public:
    int minimumMoves(vector<string> board) {
		n = board.size();
		m = board[0].size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				mat[i][j] = (board[i][j] == 'B');
			}
		}
		Prepare();//求出两种图形相对于中间位置表示
        return Solve();
    }
};

