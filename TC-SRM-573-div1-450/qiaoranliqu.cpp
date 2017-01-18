#include <vector>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class SkiResorts {
public:
	long long minCost(vector <string>, vector <int>);
};

#define fi first
#define se second
#define mp make_pair

typedef long long LL;
const int N = 55;
const LL INF = 1LL << 60;


queue<pair<int, int> > Q;
LL dp[N][N];
int tmp[N];
bool inq[N][N];

void init() {
	for (int i = 0; i < N; i++) {
		fill(dp[i], dp[i] + N, INF);
		fill(inq[i], inq[i] + N, 0);
	}
}


long long SkiResorts::minCost(vector<string> adj, vector <int> h) {
	int n = h.size();
	for (int i = 0; i < n; i++)
		tmp[i] = h[i];

	sort(tmp, tmp + n);
	init();
	
	for (int i = 0; i < n; i++) {
		dp[0][i] = abs(tmp[i] - h[0]);
		Q.push(mp(0, i));
		inq[0][i] = 1;
	}

	while (!Q.empty()) { //进行最短路操作 
		pair<int, int> cur = Q.front();
		Q.pop();
		inq[cur.fi][cur.se] = 0;

		int u = cur.fi;  //设dp_{i,j}为到第i个点,高度为h中第j小的最小代价,因为一个点不会再走2次,所以走过这个点之后不需要再记录这个答案了 
		for (int v = 0; v < n; v++)
			if (adj[u][v] != 'N') {
				for (int j = cur.se; j >= 0; j--) {
					if (dp[v][j] > dp[u][cur.se] + abs(tmp[j] - h[v])) {
						dp[v][j] = dp[u][cur.se] + abs(tmp[j] - h[v]);
						if (!inq[v][j]) {
							Q.push(mp(v, j));
						}	
					}
				}	
			}
	}

	LL res = INF;

	for (int i = 0; i < n; i++)
		res = min(res, dp[n - 1][i]);

	if (res == INF) 
		return -1;
	else
		return res;
};
