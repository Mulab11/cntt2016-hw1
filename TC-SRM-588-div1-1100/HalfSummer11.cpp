#line 2 "GameInDarknessDiv1.cpp"
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
#define maxn 3100
#define maxm 60
typedef long long ll;
using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int num[maxm][maxm];
int n, g[maxn], ei, A, B;
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int dep[maxn], pre[maxn], len[maxn];
void dfs(int x) {
	len[x] = dep[x];
	for (int i = g[x]; i; i = e[i].nxt)
		if (e[i].t != pre[x]) {
			dep[e[i].t] = dep[x] + 1;
			pre[e[i].t] = x;
			dfs(e[i].t);
			len[x] = max(len[x], len[e[i].t]);
		}
}
class GameInDarknessDiv1 {
	public:
		string check(vector <string> field) {
			int h = field.size(), w = field[0].size();
			cl(num); n = 0;
			for (int i = 0; i < h; ++i)
				for (int j = 0; j < w; ++j) {
					if (field[i][j] == '#') continue;
					num[i][j] = ++n;
					if (field[i][j] == 'A') A = n;
					if (field[i][j] == 'B') B = n;
				}
			cl(g); ei = 0;
			for (int i = 0; i < h; ++i)
				for (int j = 0; j < w; ++j) {
					if (!num[i][j]) continue;
					for (int d = 0; d < 4; ++d) {
						int x = i + dx[d], y = j + dy[d];
						if (x < 0 || x >= h || y < 0 || y >= w) continue;
						if (num[x][y]) ae(num[x][y], num[i][j]);
					}
				}
			for (int rt = 1; rt <= n; ++rt) {
				cl(dep); cl(pre); cl(len);
				dfs(rt); int cnt = 0;
				for (int i = 1; i <= n; ++i)
					if (pre[i] == rt && len[i] >= 3) ++cnt;
				if (cnt >= 3 && dep[A] >= dep[B] + 2) return "Bob wins";
			}
			return "Alice wins";
		}
};
