#include <bits/stdc++.h>

#define pii make_pair
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

int n;
int mat[maxn][maxn];
int height[maxn];
int lst[maxn], lt = 0;
LL dist[maxn][maxn];
queue<pair<int, int> > line;
bool ever[maxn][maxn] = {0};

void Solve()//Spfa求最短路
{
	pair<int, int> x;
	while (!line.empty()) {
		x = line.front();
		line.pop();
		for (int i = 1; i <= n; ++i) {
			if (mat[i][x.first] == 1) {
				for (int j = x.second; j >= 1; --j) {
					if (dist[i][j] > dist[x.first][x.second] + abs(lst[height[i]] - lst[j])) {
						dist[i][j] = dist[x.first][x.second] + abs(lst[height[i]] - lst[j]);
						if (ever[i][j] == 0) {
							ever[i][j] = 1;
							line.push(pii(i, j));
						}
					}
				}
			}
		}
	}
}

class SkiResorts {
    public:
    long long minCost(vector<string> road, vector<int> altitude) {
		n = altitude.size();
		for (int i = 1; i <= n; ++i) {
			height[i] = altitude[i - 1];//将海拔离散化
			lst[++lt] = height[i];
		}
		sort(lst + 1, lst + 1 + lt);
		lt = unique(lst + 1, lst + 1 + lt) - lst - 1;
		for (int i = 1; i <= n; ++i) {
			height[i] = lower_bound(lst + 1, lst + 1 + lt, height[i]) - lst;//求出离散化之后每个点的海拔
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				mat[i][j] = (road[i - 1][j - 1] == 'Y');
			}
		}
		memset(dist, 0x3f, sizeof(dist));//dist[i][j]表示到达第i个点，海拔为离散化之后的j的最小代价
		for (int i = 1; i <= lt; ++i) {
			dist[1][i] = abs(lst[i] - lst[height[1]]);
			ever[1][i] = 1;
			line.push(pii(1, i));
		}
		Solve();//Spfa求解最短路
		LL Ans = 2e18;
		for (int i = 1; i <= lt; ++i) {//更新答案
			Ckmin(Ans, dist[n][i]);
		}
		if (Ans > 1e18) return -1;//无解
        else return Ans;
    }
};
