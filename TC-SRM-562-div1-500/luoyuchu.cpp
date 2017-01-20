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

const int maxn = 225;

int nw, nb;
struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y):x(_x), y(_y) {}
	Point operator - (const Point &b) const
	{
		return Point(x - b.x, y - b.y);
	}
}W[maxn], B[maxn];
bitset<maxn> Db[maxn][maxn], Wb[maxn][maxn];

void Init(vector<string> wx, vector<string> wy, vector<string> bx, vector<string> by)//将字符串转为数字
{
	int tmp;
	nw = 0;
	tmp = 0;
	for (int i = 0; i < wx.size(); ++i) {
		for (int j = 0; j < wx[i].length(); ++j) {
			if (wx[i][j] == ' ') {
				W[++nw].x = tmp;
				tmp = 0;
			}
			else {
				tmp = tmp * 10 + wx[i][j] - '0';
			}
		}
	}
	W[++nw].x = tmp;
	nw = 0;
	tmp = 0;
	for (int i = 0; i < wy.size(); ++i) {
		for (int j = 0; j < wy[i].length(); ++j) {
			if (wy[i][j] == ' ') {
				W[++nw].y = tmp;
				tmp = 0;
			}
			else {
				tmp = tmp * 10 + wy[i][j] - '0';
			}
		}
	}
	W[++nw].y = tmp;
	nb = 0;
	tmp = 0;
	for (int i = 0; i < bx.size(); ++i) {
		for (int j = 0; j < bx[i].length(); ++j) {
			if (bx[i][j] == ' ') {
				B[++nb].x = tmp;
				tmp = 0;
			}
			else {
				tmp = tmp * 10 + bx[i][j] - '0';
			}
		}
	}
	B[++nb].x = tmp;
	nb = 0;
	tmp = 0;
	for (int i = 0; i < by.size(); ++i) {
		for (int j = 0; j < by[i].length(); ++j) {
			if (by[i][j] == ' ') {
				B[++nb].y = tmp;
				tmp = 0;
			}
			else {
				tmp = tmp * 10 + by[i][j] - '0';
			}
		}
	}
	B[++nb].y = tmp;
}

double Cross(const Point &a, const Point &b)//向量叉积
{
	return 1.0 * a.x * b.y - 1.0 * a.y * b.x;
}

void Prepare()
{
	for (int i = 1; i <= nb; ++i) {
		for (int j = 1; j <= nb; ++j) {
			if (i != j) {
				Db[i][j].reset();
				for (int k = 1; k <= nw; ++k) {
					if (Cross(B[j] - B[i], W[k] - B[i]) > 0) Db[i][j][k] = 1;//Db表示对于黑点i和黑点j，以i为起点，终点分别为黑点j和白点k的两个向量的叉积为正的是哪些点，Db[i][j][k]为1表示i,j,k这三点符合这个要求
				}
			}
		}
	}
	for (int i = 1; i <= nw; ++i) {
		for (int j = 1; j <= nb; ++j) {
			Wb[i][j].reset();
			for (int k = 1; k <= nw; ++k) {
				if (i != k) {
					if (Cross(B[j] - W[i], W[k] - W[i]) > 0) Wb[i][j][k] = 1;//Wb表示对于白点点i和黑点j，以i为起点，终点分别为黑点j和白点k的两个向量的叉积为正的是哪些点，Wb[i][j][k]为1表示i,j,k这三点符合这个要求
				}
			}
		}
	}
}

bool Solve()
{
	bitset<maxn> ans, full;
	full.reset();
	for (int i = 1; i <= nw; ++i) full[i] = 1;
	for (int i = 1; i <= nw; ++i) {
		for (int j = 1; j <= nb; ++j) {
			for (int k = j + 1; k <= nb; ++k) {
				ans = full;//对于一个合法的图形，要求两白点分别在两黑点两侧，且两黑点分别在两白点两侧
				if (Cross(B[k] - B[j], W[i] - B[j]) > 0) ans = ans & (full ^ Db[j][k]);
				else ans = ans & Db[j][k];
				if (Cross(B[j] - W[i], B[k] - W[i]) > 0) {
					ans = ans & Wb[i][j];
					ans = ans & (full ^ Wb[i][k]);
				}
				else {
					ans = ans & Wb[i][k];
					ans = ans & (full ^ Wb[i][j]);
				}
				ans[i] = 0;
				if (ans.count() != 0) {//枚举其中三个点，根据不同的情况使用bitset可以求出符合两个要求的第四个点的点集，若集合不为空，则存在这样的四边行
					return 1;
				}
			}
		}
	}
	return 0;
}

class CheckerFreeness {
    public:
    string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY) {
		Init(whiteX, whiteY, blackX, blackY);//将输入的字符串转化为数字
		Prepare();//求出Wb，Db数组
		if (Solve()) return "NO";
        return "YES";
    }
};

