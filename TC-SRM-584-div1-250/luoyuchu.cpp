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

int n, D;
int dist[maxn][maxn];

class Egalitarianism {
    public:
    int maxDifference(vector<string> isFriend, int d) {
		n = isFriend.size();
		for (int i = 0; i < n; ++i) {//初始化
			for (int j = 0; j < n; ++j) {
				dist[i][j] = 1e6;
			}
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (isFriend[i][j] == 'Y') {
					dist[i][j] = 1;
				}
				if (i == j) dist[i][j] = 0;
			}
		}
		for (int k = 0; k < n; ++k) {//floyd求最短路
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
		int Ans = 0;
		for (int i = 0; i < n; ++i) {//使用最长的最短路更新答案
			for (int j = 0; j < n; ++j) {
				if (dist[i][j] >= 1e6-5) {
					Ckmax(Ans, dist[i][j]);
				}
				Ckmax(Ans, dist[i][j] * d);
			}
		}
		if (Ans >= 1e6-5) return -1;
        else return Ans;
    }
};
