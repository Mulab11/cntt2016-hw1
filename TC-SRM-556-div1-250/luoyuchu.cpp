#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

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

const int maxn = 55;

int n, m;
bool touch[maxn];
bool mat[maxn][maxn];
int val[maxn];

void Dfs(int p)//Dfs遍历可达的点
{
	touch[p] = 1;
	for (int i = 0; i < n; ++i) {
		if (mat[p][i] && touch[i] == 0) {
			Dfs(i);
		}
	}
}

int Gauss()//高斯消元，用线性基，求最大异或和
{
	bool sel[maxn] = {0};
	int ans = 0;
	for (int i = 11; i >= 0; --i) {
		for (int j = 1; j <= m; ++j) {
			if (sel[j] == 0 && ((val[j] >> i) & 1)) {
				sel[j] = 1;
				for (int k = 1; k <= m; ++k) {
					if (sel[k] == 0 && ((val[k] >> i) & 1)) {
						val[k] ^= val[j];
					}
				}
				break;
			}
		}
	}
	sort(val + 1, val + 1 + m);
	reverse(val + 1, val + 1 + m);
	for (int i = 1; i <= m; ++i) {
		if ((ans ^ val[i]) > ans) {
			ans ^= val[i];
		}
	}
	return ans;
}

class XorTravelingSalesman {
    public:
    int maxProfit(vector<int> cityValues, vector<string> roads) {
		n = cityValues.size();
		memset(touch, 0, sizeof(touch));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				mat[i][j] = (roads[i][j] == 'Y');
			}
		}
		Dfs(0);//搜索每个点是否可达
		m = 0;
		for (int i = 0; i < n; ++i) {
			if (touch[i]) {
				val[++m] = cityValues[i];//取出可达的点的权值
			}
		}
		return Gauss();//求线性基，求出最大异或和
    }
};
