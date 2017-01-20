/* Copyright 2016 AcrossTheSky */
#include <iostream>
#include <cstdio>
#include <utility>
#include <cassert>
#include <map>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <bitset>
#include <fstream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define PER(i, a, b) for (int i = (a); i >= (b); --i)
#define RVC(i, c) fot (int i = 0; i < (c).size(); ++i)
#define RED(k, u) for (int k = head[(u)]; k; k = edge[k].next)
#define lowbit(x) ((x) & (-(x)))
#define CL(x, v) memset(x, v, sizeof x)
#define MP std::make_pair
#define PB push_back
#define FR first
#define SC second
#define rank rankk
#define next nextt
#define link linkk
#define index indexx
#define abs(x) ((x) > 0 ? (x) : (-(x)))
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

template<class T> inline
bool getmin(T *a, const T &b) {
	if (b < *a) {
		*a = b;
		return true;
	}
	return false;
}

template<class T> inline
bool getmax(T *a, const T &b) {
	if (b > *a) {
		*a = b;
		return true;
	}
	return false;
}

const int mo = 1000000007;
template<class T>
T pow(T a, T b, int c = mo) {
	T res = 1;
	for (T i = 1; i <= b; i <<= 1, a = 1LL * a * a % c) if (b & i) res = 1LL * res * a % c;
	return res;
}

/*======================= TEMPLATE =======================*/
const int N = 5100;
const int inf = 1e9;
struct node { 
	int p, w, next;
}edge[N * 5];
int head[N], h[N], cnt;
int s, t;
void ae(int a, int b, int c) {
	edge[++cnt].p = b;
	edge[cnt].next = head[a];
	edge[cnt].w = c;
	head[a] = cnt;

	edge[++cnt].p = a;
	edge[cnt].next = head[b];
	edge[cnt].w = 0;
	head[b] = cnt;
}

bool bfs() { // dinic
	static queue<int> q;
	while (!q.empty()) q.pop();
	REP(i, 1, t) h[i] = -1;
	h[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		RED(k, u) if (edge[k].w) {
			int v = edge[k].p;
			if (h[v] == -1) {
				h[v] = h[u] + 1;
				if (v == t) return true;
				q.push(v);
			}
		}
	}
	return false;
}

int dfs(int u, int now) { //dinic
	if (u == t) return now;
	int res = 0, tmp;
	RED(k, u) {
		int v = edge[k].p;
		if (edge[k].w && h[v] == h[u] + 1) {
			tmp = dfs(v, min(now, edge[k].w));
			edge[k].w -= tmp;
			edge[k ^ 1].w += tmp;
			res += tmp;
			if (!(now -= tmp)) break;
		}
	}
	if (!res) h[u] = -1;
	return res;
}

int dinic() { //dinic
	int res = 0;
	while (bfs()) {
		res += dfs(s, inf);
	}
	return res;
}

int id[51][51];

class FoxAndGo3 {
	public:
		int maxEmptyCells(vector<string> board) {
			int n = board.size();
			CL(head, 0);
			cnt = 1;
			s = n * n + 1;  t = n * n + 2;
			int tot = 0, ans = 0;
			REP(i, 0, n - 1) REP(j, 0, n - 1) id[i][j] = ++tot;
			REP(i, 0, n - 1) REP(j, 0, n - 1) if (board[i][j] == 'o') 
				ae(s, id[i][j], 1), ++ans;
			else if (board[i][j] == '.') ae(id[i][j], t, 1), ++ans;
			REP(i, 0, n - 1) REP(j, 0, n - 1) if (board[i][j] == 'o') {
				if (i && board[i - 1][j] == '.') ae(id[i][j], id[i - 1][j], inf);
				if (j && board[i][j - 1] == '.') ae(id[i][j], id[i][j - 1], inf);
				if (i < n - 1 && board[i + 1][j] == '.') ae(id[i][j], id[i + 1][j], inf);
				if (j < n - 1 && board[i][j + 1] == '.') ae(id[i][j], id[i][j + 1], inf);
			}
			return ans - dinic();
		}
};

// Powered by Greed 2.0-RC
