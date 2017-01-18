#line 5 "CurvyonRails.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int walk[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

const int maxn = 25, maxm = 25;

int n, m;
char c[maxn + 5][maxm + 5];

const int max0 = 10000, max1 = 100000;

struct edge
{
    int id, g, w, nxt;
 
    edge() { }
    edge(const int &_id, const int &_g, const int &_w, const int &_nxt): id(_id), g(_g), w(_w), nxt(_nxt) { }
 
};
 
int st[max0 + 5], en = 0;
edge e[max1 + 5];
 
inline void add_edge(const int &x, const int &y, const int &z, const int &w)
{
    e[en] = edge(y, z, w, st[x]), st[x] = en++; 
}
 
inline void add_biedge(int x, int y, int z, const int &w)
{
    if (!z) return;
    if (z < 0) swap(x, y), z = -z;
    add_edge(x, y, z, w);
    add_edge(y, x, 0, -w);
}
 
int S, T;
 
int ans = 0;
 
int SPFA()
{
    static int dis[max0 + 5];
    static int q[max0 + 5];
    static bool vis[max0 + 5] = {0};
    static int pre[max0 + 5], Min[max0 + 5];
    int head = 0, rear = 0;
    memset(vis, 0, sizeof vis);
    memset(dis, oo, sizeof dis);
    q[rear++] = S;
    dis[S] = 0;
    Min[S] = oo;
    while (head != rear)
    {
        const int &x = q[head++];
        vis[x] = 0;
        if (head >= max0 + 1) head -= max0 + 1;
        for (int i = st[x]; i != -1; i = e[i].nxt)
        {
            if (!e[i].g) continue;
            const int &y = e[i].id;
            if (chkmin(dis[y], dis[x] + e[i].w))
            {
                Min[y] = min(Min[x], e[i].g);
                pre[y] = i;
                if (!vis[y])
                {
                    vis[y] = 1;
                    q[rear++] = y;
                    if (rear >= max0 + 1) rear -= max0 + 1;
                }
            }
        }
    }
    if (dis[T] >= oo) return 0;
    int u = T;
    while (u != S)
    {
        e[pre[u]].g -= Min[T];
        e[pre[u] ^ 1].g += Min[T];
        u = e[pre[u] ^ 1].id;
    }
    ans += dis[T] * Min[T];
    return Min[T];
}

inline int id(int x, int y, int z) { return ((x * m) + y) << 1 | z; }

class CurvyonRails
{
	public:
		int getmin(vector <string> field)
		{
			n = SZ(field);
			m = SZ(field[0]);
			REP(i, 0, n) REP(j, 0, m) c[i][j] = field[i][j];
			memset(st, -1, sizeof st), en = 0;
			S = n * m << 1, T = n * m << 1 | 1;
			int sum = 0;
			REP(i, 0, n) REP(j, 0, m)
			{
				if (c[i][j] == 'w') continue;
				++sum;
				bool ty = (i ^ j) & 1;
				if (ty) REP(k, 0, 2) add_biedge(S, id(i, j, k), 1, 0);
				else REP(k, 0, 2) add_biedge(id(i, j, k), T, 1, 0);
				add_biedge(id(i, j, 0), id(i, j, 1), 1, c[i][j] == 'C');
				add_biedge(id(i, j, 1), id(i, j, 0), 1, c[i][j] == 'C');
				if (ty)
				{
					REP(k, 0, 4)
					{
						int u = i + walk[k][0], v = j + walk[k][1];
						if (u < 0 || u >= n || v < 0 || v >= m || c[u][v] == 'w') continue;
						add_biedge(id(i, j, k & 1), id(u, v, k & 1), 1, 0);
					}
				}
			}
			ans = 0;
			int tmp;
			while ((tmp = SPFA())) sum -= tmp;
			assert(sum >= 0);
			if (sum) return -1;
			return ans;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
