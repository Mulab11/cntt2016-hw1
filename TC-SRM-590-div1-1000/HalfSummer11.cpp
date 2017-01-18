#line 2 "FoxAndCity.cpp"
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
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 2010
#define maxm 50
typedef long long ll;
using namespace std;
int n, s, t, g[maxn], cur[maxn], ei, dis[maxn], q[maxn], qh, qt;
struct edge{
	int t, c, nxt;
}e[maxn * maxn];
void init()
{
	memset(g, 0, sizeof(g)); ei = 1;
}
void ae(int a, int b, int c)
{
	e[++ ei].t = b; e[ei].nxt = g[a]; g[a] = ei; e[ei].c = c;
	e[++ ei].t = a; e[ei].nxt = g[b]; g[b] = ei; e[ei].c = 0;
}
bool bfs()
{
	memset(dis, -1, sizeof(dis));
	q[qh = qt = 1] = s; dis[s] = 0; int x;
	while (qh <= qt){
		x = q[qh ++];
		for (int i = g[x]; i; i = e[i].nxt)
			if (e[i].c && dis[e[i].t] == -1){
				dis[e[i].t] = dis[x] + 1;
				q[++ qt] = e[i].t;
			}
	}
	return dis[t] != -1;
}
int dfs(int x, int f)
{
	if (x == t) return f;
	int d, u = 0;
	for (int &i = cur[x]; i; i = e[i].nxt)
		if (e[i].c && dis[e[i].t] == dis[x] + 1){
			d = dfs(e[i].t, min(e[i].c, f - u));
			e[i].c -= d; e[i ^ 1].c += d; u += d;
			if (u == f) return u;
		}
	if (! u) dis[x] = -42;
	return u;
}
int dinic()
{
	int ret = 0;
	while (bfs()){
		memcpy(cur, g, sizeof(g));
		ret += dfs(s, oo);
	}
	return ret;
}
int mul(int x){return x * x;}
class FoxAndCity
{
	public:
		int minimalCost(vector <string> linked, vector <int> want)
		{
			init();
			n = linked.size();
			for (int i = 0; i < n; ++ i)
				for (int j = 0; j < n; ++ j)
					if (linked[i][j] == 'Y')
						for (int d = 2; d <= n - 1; ++ d)
							ae(j * n + d, i * n + d - 1, oo);
			s = n * n + 1; t = s + 1;
			ae(s, 1, mul(want[0]));
			for (int d = 1; d < n - 1; ++ d) ae(d, d + 1, oo);
			ae(n - 1, t, oo);
			for (int i = 1; i < n; ++ i){
				ae(s, i * n + 1, oo);
				for (int d = 1; d < n - 1; ++ d) ae(i * n + d, i * n + d + 1, mul(want[i] - d));
				ae(i * n + n - 1, t, mul(want[i] - (n - 1)));
			}
			return dinic();
		}
		

};
