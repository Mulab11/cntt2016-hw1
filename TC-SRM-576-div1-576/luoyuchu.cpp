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

const int maxn = 305;
const int mod = 1e9+9;

int n, m, L, R, len;
int A[maxn];
int f[maxn][maxn][2];//f[i][j][0/1]表示到了第i位，最近的连续的一段是否出现了一个完整的海绵，一共放置了j个海绵的情况

int Solve()//Dp求解
{
	memset(f, 0, sizeof(f));
	for (int i = 0; i <= n; ++i) f[i][0][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= m; ++j) {
			int s = 0;
			for (int k = 1; k <= len; ++k) {
				if (i + k > n) break;
				s += A[i + k];
				if (s > R) break;
				if (s >= L) {
					(f[i + k][j + 1][1] += f[i][j][1]) %= mod;
					if (k < len) {
						(f[i + k][j + 1][0] += f[i][j][0]) %= mod;
					}
					if (k == len) {//放了一段完整的海绵
						(f[i + k][j + 1][1] += f[i][j][0]) %= mod;
					}
				}
			}
			for (int k = 1; k <= n; ++k) {//空着一段不放海绵
				if (i + k > n) break;
				(f[i + k][j][0] += f[i][j][1]) %= mod;
			}
		}
	}
	int Ans = 0;
	for (int i = 0; i <= n; ++i) {//统计答案
		(Ans += f[i][m][1]) %= mod;
	}
	return Ans;
}

class TheExperiment {
    public:
    int countPlacements(vector<string> in, int M, int Len, int _A, int _B) {
		n = 0;
		for (int i = 0; i < (int)in.size(); ++i) {
			for (int j = 0; j < (int)in[i].length(); ++j) {
				A[++n] = in[i][j] - '0';
			}
		}
		m = M;
		len = Len;
		L = _A;
		R = _B;
		return Solve();//Dp计算答案
    }
};

