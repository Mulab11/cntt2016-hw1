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
const int inf = 1e9;
int val(char c) { // 把字符转化成对应的数
    if (isdigit(c)) return c - '0';
    if (c >= 'a') return c - 'a' + 10;
    else return c - 'A' + 36;
}
struct node { 
    int p, w, next;
}edge[10000];
int head[10000], h[10000], cnt;
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

int n, m;

int id[100][100];

void addadj(int x, int y) { // 给相邻的点连边
    if (x) ae(id[x][y] * 2 - 1, id[x - 1][y] * 2, inf), ae(id[x][y] * 2, id[x - 1][y] * 2 - 1, inf);
    if (y) ae(id[x][y] * 2 - 1, id[x][y - 1] * 2, inf), ae(id[x][y] * 2, id[x][y - 1] * 2 - 1, inf);
    if (x < n - 1) ae(id[x][y] * 2 - 1, id[x + 1][y] * 2, inf), ae(id[x][y] * 2, id[x + 1][y] * 2 - 1, inf);
    if (y < m - 1) ae(id[x][y] * 2 - 1, id[x][y + 1] * 2, inf), ae(id[x][y] * 2, id[x][y + 1] * 2 - 1, inf);
}

class SurroundingGame {
	public:
		int maxScore(vector<string> cost, vector<string> benefit) {
            CL(head, 0);
            cnt = 1;
            n = cost.size(), m = cost[0].size();
            int tot = 0;
            REP(i, 0, n - 1) 
                REP(j, 0, m - 1) id[i][j] = ++tot; //给网格中所有点标号
            s = 2 * tot + 1; t = s + 1;// 设置源点和汇点
            
            int sum = 0;
            REP(i, 0, n - 1) REP(j, 0, m - 1) sum += val(benefit[i][j]);

            REP(i, 0, n - 1)  //建图
                REP(j, 0, m - 1) 
                if ((i & 1) ^ (j & 1)) ae(s, 2 * id[i][j] - 1, val(cost[i][j])), 
                    ae(2 * id[i][j] - 1, 2 * id[i][j], val(benefit[i][j])), addadj(i, j);
                else  ae(2 * id[i][j] - 1, t, val(cost[i][j])), 
                    ae(2 * id[i][j], 2 * id[i][j] - 1, val(benefit[i][j]));

            cerr << sum <<' ' << tot << endl;

            return sum - dinic();
		}
};