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

const int maxn = 605;
const int maxm = 35;

int n;
int A[maxn];
int C[maxm][maxm];

void Prepare()
{
	for (int i = 0; i <= 31; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

double Solve()
{
	int me = A[1];
	int R;
	double Exp = 0;
	sort(A + 1, A + 1 + n);
	reverse(A + 1, A + 1 + n);
	R = n / 20 + (n % 20 > 0);
	for (int i = 1; i <= n; i += R) {
		bool ok = 1;
		for (int j = 0; j < R; ++j) {//如果这一批人中间有Elly，则这批人已经确定
			if (A[i + j] == me) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			if (i + R - 1 <= n) {//如果这批人是满的，直接用raing乘以概率
				for (int j = 0; j < R; ++j) {
					Exp += A[i + j] * 1.0 / R;
				}
			}
			else {
				int g = n - i + 1;
				double e = 0;
				for (int j = 0; j < g; ++j) {
					e += A[i + j] * 1.0 / g;
				}
				return (Exp + e) * C[R - 1][g - 1] / C[R][g] / (n / R + 1) + Exp / (n / R) * (C[R][g] - C[R - 1][g - 1]) / C[R][g];//否则，分成是否分到额外的一个人分别计算期望
			}
		}
		else {
			Exp += me;
		}
	}
	return Exp / (n / R + (n % R > 0));
}

class EllysRoomAssignmentsDiv1 {
    public:
    double getAverage(vector<string> ratings) {
		int s = 0;
		n = 0;
		memset(A, 0, sizeof(A));
		for (int i = 0; i < (int)ratings.size(); ++i) {//读入
			for (int j = 0; j < (int)ratings[i].length(); ++j) {
				if (ratings[i][j] != ' ') {
					s = s * 10 + ratings[i][j] - '0';
				}
				else {
					A[++n] = s;
					s = 0;
				}
			}
		}
		if (s > 0) A[++n] = s;
		Prepare();//预处理组合数
		return Solve();//计算期望
    }
};
