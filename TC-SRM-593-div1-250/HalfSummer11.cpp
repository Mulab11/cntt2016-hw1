#line 2 "HexagonalBoard.cpp"
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
typedef long long ll;
using namespace std;
int n, m, num[maxn][maxn];
int g[maxn * maxn], ei;
struct edge {
	int t, nxt;
}e[maxn * maxn * 6];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int col[maxn * maxn];
const int dx[] = {0, 1, 1};
const int dy[] = {1, -1, 0};
bool color(int x, int c) {
	col[x] = c;
	for (int i = g[x]; i; i = e[i].nxt) {
		if (col[e[i].t] && col[e[i].t] + c != 3) return 0;
		if (!col[e[i].t] && !color(e[i].t, 3 - c)) return 0;
	}
	return 1;
}
class HexagonalBoard {
	public:
		int minColors(vector <string> board) {
			bool flag = 1; cl(num); n = 0;
			m = board.size();
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < m; ++j)
					if (board[i][j] == 'X') num[i][j] = ++n;
			cl(g); ei = 0;
			for (int i = 0; i < m; ++i)
				for (int j = 0; j < m; ++j)
					if (num[i][j]) {
						for (int d = 0; d < 3; ++d) {
							int x = i + dx[d], y = j + dy[d];
							if (x >= 0 && x < m && y >= 0 && y < m && num[x][y]) {
								flag = 0;
								ae(num[i][j], num[x][y]);
								ae(num[x][y], num[i][j]);
							}
						}
					}
			if (!n) return 0;
			if (flag) return 1;
			cl(col);
			for (int i = 1; i <= n; ++i) 
				if (!col[i]) {
					if (!color(i, 1)) return 3;
				}
			return 2;
		}
};
