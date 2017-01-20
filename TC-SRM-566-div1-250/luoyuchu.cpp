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
int du[maxn];//每个点的度数
bool mat[maxn][maxn];//邻接矩阵

class PenguinSledding {
    public:
    long long countDesigns(int numCheckpoints, vector<int> checkpoint1, vector<int> checkpoint2) {
		long long Ans = 0;
		n = numCheckpoints;
		memset(du, 0, sizeof(du));
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < checkpoint1.size(); ++i) {
			++du[checkpoint1[i]];
			++du[checkpoint2[i]];
			mat[checkpoint1[i]][checkpoint2[i]] = 1;
			mat[checkpoint2[i]][checkpoint1[i]] = 1;
		}
		for (int i = 1; i <= n; ++i) {//如果要合法，可以选择共一个顶点的边集
			Ans += (1LL << du[i]) - 1;
		}
		Ans -= checkpoint1.size();//单独一条边被算两次
		Ans += 1;//空集
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				for (int k = j + 1; k <= n; ++k) {//也可以选择形成一个三角形的三条边
					if (mat[i][j] && mat[j][k] && mat[i][k]) {
						++Ans;
					}
				}
			}
		}
        return Ans;
    }
};

