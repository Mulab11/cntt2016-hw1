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
const int walk[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m, Ans = 0;
int mat[maxn][maxn];
bool vis[maxn][maxn];
int lft[maxn], rgt[maxn], mid[maxn];//lft和rgt表示最左和最右的两列的每一行转化为括号序列是左括号还是右括号，mid则表示这一行左边与右边括号相反
int End[3][2], e_cnt = 0;//搜索出来的这条隧道的两个或一个端点
int f[maxn][maxn][maxn] = {0};//Dp数组

void Dfs(int x, int y)//搜索隧道的端点
{
	int out = 0;
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int tx = x + walk[i][0];
		int ty = y + walk[i][1];
		if (tx >= 1 && tx <= n && ty >= 1 && ty <= m && mat[tx][ty]) {
			++out;
			if (vis[tx][ty] == 0) {
				Dfs(tx, ty);
			}
		}
	}
	if (out <= 1) {
		++e_cnt;
		End[e_cnt][0] = x;
		End[e_cnt][1] = y;
	}
}

bool Onbound(int x, int y)//是否在边界上
{
	return (x == 1 || y == 1 || x == n || y == m);
}

int Beside(int y)//是否在左右边界上
{
	return (y == 1 || y == m);
}

void Getall()//求出所有的lft,rgt,mid数组
{
	Ans = 0;
	memset(rgt, 0, sizeof(rgt));
	memset(lft, 0, sizeof(lft));
	memset(mid, 0, sizeof(mid));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (mat[i][j] && vis[i][j] == 0) {
				e_cnt = 0;
				Dfs(i, j);//先搜索端点
				assert(e_cnt <= 2);
				if (e_cnt == 1) {//只有一个点的情况
					if (End[1][0] == 1) {//如果在顶部，则一定要一条新的隧道，如果同时在侧面，则可以作为一个左括号
						++Ans;
						if (End[1][1] == 1) lft[End[1][0]] = 1;
						else if (End[1][1] == m) rgt[End[1][0]] = 1;
					}
					else {//否则如果在侧面，作为右括号
						if (End[1][1] == 1) lft[End[1][0]] = -1;
						else if (End[1][1] == m) rgt[End[1][0]] = -1;
					}
				}
				else if (Onbound(End[1][0], End[1][1]) + Onbound(End[2][0], End[2][1]) == 1) {//如果只有一个端点在边界上，只需考虑那一个
					if (Onbound(End[2][0], End[2][1]) == 1) {
						swap(End[1][0], End[2][0]);
						swap(End[1][1], End[2][1]);
					}
					if (End[1][1] == 1) lft[End[1][0]] = -1;
					else if (End[1][1] == m) rgt[End[1][0]] = -1;
					else ++Ans;
				}
				else {
					if (Beside(End[1][1]) && Beside(End[2][1]) && End[1][0] == End[2][0]) {//如果在同一行的两侧，则括号内相反
						mid[End[1][0]] = 1;
						continue;
					}
					if (End[1][0] == End[2][0] && (Beside(End[1][1]) + Beside(End[2][1])) == 1 && End[1][0] == 1) {//如果同时在第一行，则从上面连入，如果贴边界，则有一个左括号
						if (Beside(End[2][1])) End[1][0] = End[2][0], End[1][1] = End[2][1];
						++Ans;
						if (End[1][1] == 1) lft[End[1][0]] = 1;
						else if (End[1][1] == m) rgt[End[1][0]] = 1;
						continue;
					}
					if (End[1][0] == End[2][0] && (Beside(End[1][1]) + Beside(End[2][1])) == 1) {//如果同在非第一行的一行，则贴边界的那一个为左括号
						if (Beside(End[2][1])) End[1][0] = End[2][0], End[1][1] = End[2][1];
						if (End[1][1] == 1) lft[End[1][0]] = -1;
						else if (End[1][1] == m) rgt[End[1][0]] = -1;
						else ++Ans;
						continue;
					}
					if (End[1][0] == End[2][0]) {//如果没有人贴着左右边界，由于题目保证合法，只需++Ans
						++Ans;
						continue;
					}
					if (End[1][0] < End[2][0]) {
						swap(End[1][0], End[2][0]);
						swap(End[1][1], End[2][1]);
					}
					if (End[1][1] == End[2][1] && End[2][0] != 1 && End[1][0] - 1 == End[2][0]) {//由于隧道不能相交，所以连续两个竖着在边界上时不能一个作为左括号一个作为右括号，应只有一个左括号
						if (End[2][1] == 1) lft[End[2][0]] = -1;
						else if (End[2][1] == m) rgt[End[2][0]] = -1;
						else ++Ans;
						continue;
					}
					else {//否则无特殊情况下，对两个端点分别判读即可
						if (End[1][1] == 1) lft[End[1][0]] = 1;
						else if (End[1][1] == m) rgt[End[1][0]] = 1;
						if (End[2][1] == 1) lft[End[2][0]] = -1;
						else if (End[2][1] == m) rgt[End[2][0]] = -1;
						else ++Ans;
					}
				}
			}
		}
	}
}

int Solve()//Dp求最小
{
	memset(f, 0x3f, sizeof(f));
	f[0][0][0] = 0;//f[i][j][k]表示当前决策到了第i行，左边栈里有j个左括号，右边栈里有k个左括号
	for (int i = 1; i <= n; ++i) {
		for (int x = 0; x <= n; ++x) {
			for (int y = 0; y <= n; ++y) {
				if (f[i - 1][x][y] > 1e9) continue;
				if (mid[i] == 1) {//考虑哪一边放左括号，哪一边右括号
					Ckmin(f[i][x - (x > 0)][y + 1], f[i - 1][x][y] + (x == 0));
					Ckmin(f[i][x + 1][y - (y > 0)], f[i - 1][x][y] + (y == 0));
				}
				else {//已经确定，直接转移
					Ckmin(f[i][max(0, x + lft[i])][max(0, y + rgt[i])], f[i - 1][x][y] + (lft[i] == -1 && x == 0) + (rgt[i] == -1 && y == 0));
				}
			}
		}
	}
	int Min = 2e9;
	for (int i = 0; i <= n; ++i) {//找出最小值，更新答案
		for (int j = 0; j <= n; ++j) {
			Ckmin(Min, f[n][i][j]);
		}
	}
	return Min;
}

int One()
{
	for (int i = 1; i <= n; ++i) {
		if (mat[i][m]) {
			return 1;
		}
	}
	return 0;
}

class Tunnels {
    public:
    int minimumTunnels(vector<string> frame) {
		n = frame.size();
		m = frame[0].length();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				mat[i][j] = (frame[i - 1][j - 1] == 'X');
			}
		}
		if (m == 1) return One();//对于只有一列，最多答案为1
		Getall();//求出两边括号序列
        return Solve() + Ans;//Dp求解
    }
};

