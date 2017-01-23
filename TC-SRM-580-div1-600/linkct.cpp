#include <bits/stdc++.h>
using namespace std;
typedef vector <string> vs;
const int MAXN = 2505, INF = 0x3f3f3f3f;

class ShoutterDiv1{
public:
	int d1[MAXN], d2[MAXN], st[MAXN], ed[MAXN], n;
	bool g[MAXN][MAXN];
	void bfs(int s, int d[]){
		int i; queue <int> q;
		memset(d, 0x3f, sizeof(int) * (n + 1));
		d[s] = 1, q.push(s);
		while(!q.empty()){
			s = q.front(); q.pop();
			for(i = 1; i <= n; ++ i)
				if(g[s][i] && d[i] > d[s] + 1){
					d[i] = d[s] + 1;
					q.push(i);
				}
		}
	}
	int count(vs s1000, vs s100, vs s10, vs s1, vs t1000, vs t100, vs t10, vs t1){
		int i, j, cur, sum = 0, mnp = -1, mxp = -1, mnt = INF, mxs = -1;
		for(i = 0; i < int(s1.size()); ++ i)
			for(j = 0; j < int(s1[i].length()); ++ j){
				++ n;
				st[n] = (s1000[i][j] - '0') * 1000 + (s100[i][j] - '0') * 100 + (s10[i][j] - '0') * 10 + (s1[i][j] - '0');
				ed[n] = (t1000[i][j] - '0') * 1000 + (t100[i][j] - '0') * 100 + (t10[i][j] - '0') * 10 + (t1[i][j] - '0');
				if(ed[n] < mnt) mnt = ed[n], mnp = n;
				if(st[n] > mxs) mxs = st[n], mxp = n;
			}
		for(i = 1; i <= n; ++ i)
			for(j = i + 1; j <= n; ++ j)
				if(max(st[i], st[j]) <= min(ed[i], ed[j]))
					g[i][j] = g[j][i] = true;
		bfs(mnp, d1);
		bfs(mxp, d2);
		for(i = 1; i <= n; ++ i){
			cur = max(d1[i] - 2, 0) + max(d2[i] - 2, 0);
			for(j = 1; j <= n; ++ j)
				if(g[i][j]) cur = min(cur, max(d1[j] - 2, 0) + max(d2[j] - 2, 0) + 1);
			if(cur > n) return -1;
			sum += cur;
		} return sum;
	}
};
