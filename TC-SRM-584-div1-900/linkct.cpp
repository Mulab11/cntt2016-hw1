#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

class FoxTheLinguist{
public:
	int f[1035][105], g[105], nxt[705], to[705], val[705], edgeSize, m;
	bool inq[105]; queue <int> q;
	inline bool update(int &a, int b){if(a <= b) return false; a = b; return true;}
	void addEdge(int u, int v, int w){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
		val[edgeSize] = w;
	}
	int minimalHours(int n, vector <string> courses){
		int i, j, k, *dis, u, v, w, N;
		string course;
		memset(g, 0, sizeof(g));
		edgeSize = 0;
		for(i = 0; i < n; ++ i){
			addEdge(i * 10, n * 10, 0);
			for(j = 1; j < 10; ++ j)
				addEdge(i * 10 + j - 1, i * 10 + j, 0);
		}
		for(i = 0; i < int(courses.size()); ++ i)
			course += courses[i];
		for(i = 0, m = course.length() / 12 + 1; i < m; ++ i){
			u = (course[i * 12] - 'A') * 10 + (course[i * 12 + 1] - '0');
			v = (course[i * 12 + 4] - 'A') * 10 + (course[i * 12 + 5] - '0');
			w = (course[i * 12 + 7] - '0') * 1000 + (course[i * 12 + 8] - '0') * 100 + (course[i * 12 + 9] - '0') * 10 + (course[i * 12 + 10] - '0');
			addEdge(v, u, w);
		}
		memset(f, 0x3f, sizeof(f));
		memset(inq, false, sizeof(inq));
		for(i = 0; i < n; ++ i)
			f[1 << i][i * 10 + 9] = 0;
		for(i = 1, N = 1 << n; i < N; ++ i){
			for(j = 0; j <= n * 10; ++ j){
				for(k = (i - 1) & i; k; k = (k - 1) & i)
					update(f[i][j], f[k][j] + f[i ^ k][j]);
				q.push(j), inq[j] = true;
			} dis = f[i];
			while(!q.empty()){
				j = q.front(); q.pop();
				for(k = g[j]; k; k = nxt[k])
					if(update(dis[to[k]], dis[j] + val[k]) && !inq[to[k]])
						inq[to[k]] = true, q.push(to[k]);
				inq[j] = false;
			}
		} return f[N - 1][n * 10] == INF ? -1 : f[N - 1][n * 10];
	}
};
