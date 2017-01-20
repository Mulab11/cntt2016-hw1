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

const int maxn = 105;

int n, m;
char mat[maxn][maxn];
int po[255];

class PastingPaintingDivOne {
    public:
    vector<long long> countColors(vector<string> cp, int T) {
		vector<long long> sum;
		n = cp.size();
		m = cp[0].length();
		po['R'] = 0;
		po['G'] = 1;
		po['B'] = 2;//将字符映射到数字
		int Try = min(max(n, m), T);
		LL unit[3] = {0};
		sum.resize(3);
		memset(mat, 0, sizeof(mat));
		for (int i = 1; i <= Try; ++i) {//先暴力做Try遍
			for (int a = 0; a < n; ++a) {
				for (int b = 0; b < m; ++b) {
					if (cp[a][b] != '.') {
						mat[i + a][i + b] = cp[a][b];
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {//求出在足够多次之后的循环节
			if (mat[Try + i][Try] != '\0') {
				++unit[po[mat[Try + i][Try]]];
			}
		}
		for (int i = 1; i < m; ++i) {
			if (mat[Try][Try + i] != '\0') {
				++unit[po[mat[Try][Try + i]]];
			}
		}
		for (int i = 1; i < maxn; ++i) {//统计这Try遍的答案
			for (int j = 1; j < maxn; ++j) {
				if (mat[i][j] != '\0') {
					++sum[po[mat[i][j]]];
				}
			}
		}
		if (Try != T) {//若Try小于T，则加上循环节的若干次
			for (int i = 0; i < 3; ++i) {
				sum[i] += (T - Try) * unit[i];
			}
		}
		return sum;
    }
};

