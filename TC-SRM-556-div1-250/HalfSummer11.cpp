#line 2 "XorTravelingSalesman.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define maxm 2010
typedef long long ll;
using namespace std;
bool f[maxn][maxm]; // f[i][j]为1，表示存在一个状态，其中人位于第i个点，手上的数字是j
pii q[maxn * maxm]; // bfs的队列
int n, qh, qt, ans;
class XorTravelingSalesman {
	public:
		int maxProfit(vector <int> V, vector <string> G) {
			ans = V[0]; n = V.size();
			cl(f); f[0][V[0]] = 1; q[qh = qt = 1] = mp(0, V[0]); // 初始状态是(0, V[0])
			pii now;
			while (qh <= qt) {
				now = q[qh++];
				for (int j = 0; j < n; ++j)
					if (j != now.fr && G[now.fr][j] == 'Y')  // bfs扩展状态
						if (!f[j][now.sc ^ V[j]]) {
							f[j][now.sc ^ V[j]] = 1;
							ans = max(ans, now.sc ^ V[j]); // 记录所有可达状态中手上数字的最大值
							q[++qt] = mp(j, now.sc ^ V[j]);
						}
			}
			return ans;
		}
};
