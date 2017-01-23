#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 105;

double dis[MAXN][MAXN], mind[MAXN];
int current, n; map <int, map <int, int> > ct;
vector <int> sub[MAXN], sup[MAXN], r;
queue <int> q; bool g[MAXN][MAXN], vis[MAXN];
inline bool cmp(const int &a, const int &b){
	return dis[current][a] - r[a] < dis[current][b] - r[b];
}
class CandyOnDisk{
public:
	inline int dcmp(double x){return fabs(x) <= 1e-5 ? 0 : (x >= 0.0 ? 1 : -1);}
	void addEdge(int u, int v){g[u][v] = true;}
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r_, int sx, int sy, int tx, int ty){
		if(sx == tx && sy == ty) return "YES";
		int i, j, now; LL d2; double d, rht;
		memset(g, false, sizeof(g));
		memset(vis, false, sizeof(vis));
		r = r_;
		for(i = 0; i < int(x.size()); ++ i)
			if(ct[x[i]][y[i]] == 0)
				ct[x[i]][y[i]] = r[i];
			else ct[x[i]][y[i]] = max(ct[x[i]][y[i]], r[i]);
		x.clear(), y.clear(), r.clear();
		map <int, map <int, int> > :: iterator it1;
		map <int, int> :: iterator it2;
		for(it1 = ct.begin(); it1 != ct.end(); ++ it1)
			for(it2 = it1 -> second.begin(); it2 != it1 -> second.end(); ++ it2)
				x.push_back(it1 -> first), y.push_back(it2 -> first), r.push_back(it2 -> second);
		n = x.size();
		for(i = 0; i < n; ++ i)
			mind[i] = 1e10;
		for(i = 0; i < n; ++ i)
			for(j = i + 1; j < n; ++ j){
				d2 = LL(x[i] - x[j]) * (x[i] - x[j]) + LL(y[i] - y[j]) * (y[i] - y[j]);
				dis[i][j] = dis[j][i] = d = sqrt(d2 * 1.0);
				if(d2 > LL(r[i] + r[j]) * (r[i] + r[j])) continue;
				if(dcmp(d + r[j] - r[i]) <= 0){
					sup[j].push_back(i);
					sub[i].push_back(j);
				}else if(dcmp(d + r[i] - r[j]) <= 0){
					sup[i].push_back(j);
					sub[j].push_back(i);
				}else{
					addEdge(i, j), addEdge(j, i);
					mind[i] = min(mind[i], max(d - r[j], 0.0));
					mind[j] = min(mind[j], max(d - r[i], 0.0));
				}
			}
		for(i = 0; i < n; ++ i){
			d2 = LL(x[i] - sx) * (x[i] - sx) + LL(y[i] - sy) * (y[i] - sy);
			current = i, sort(sub[i].begin(), sub[i].end(), cmp);
			addEdge(n + i, i); d = sqrt(d2 * 1.0);
			if(!sup[i].empty()) addEdge(i, n + i);
			if(!sub[i].empty()){
				if(dcmp(mind[i] - dis[i][sub[i][0]] - r[sub[i][0]]) <= 0){
					addEdge(i, n + sub[i][0]);
					addEdge(n + sub[i][0], i);
				}
				if(dcmp(dis[i][sub[i][0]] + r[sub[i][0]] - r[i]) == 0)
					addEdge(n + sub[i][0], i);
				for(j = 1, rht = dis[i][sub[i][0]] + r[sub[i][0]]; j < int(sub[i].size()); ++ j){
					if(dcmp(dis[i][sub[i][j]] + r[sub[i][j]] - r[i]) == 0)
						addEdge(n + sub[i][j], i);
					if(dcmp(mind[i] - dis[i][sub[i][j]] - r[sub[i][j]]) <= 0){
						addEdge(i, n + sub[i][j]);
						addEdge(n + sub[i][j], i);
					}
					if(dcmp(rht - dis[i][sub[i][j]] - r[sub[i][j]]) >= 0){
						addEdge(n + sub[i][j - 1], n + sub[i][j]);
						addEdge(n + sub[i][j], n + sub[i][j - 1]);
						rht = max(rht, dis[i][sub[i][j]] + r[sub[i][j]]);
					}else rht = dis[i][sub[i][j]] + r[sub[i][j]];
				}
			} if(d2 > LL(r[i]) * r[i]) continue;
			if(d2 == LL(x[i] - tx) * (x[i] - tx) + LL(y[i] - ty) * (y[i] - ty)) return "YES";
			if(!sup[i].empty() && !vis[n + i]){
				vis[n + i] = true;
				q.push(n + i);
			}
			if(d2 < LL(r[i]) * r[i]){
				if(dcmp(d - mind[i]) >= 0 && !vis[i])
					vis[i] = true, q.push(i);
				for(j = 0; j < int(sub[i].size()); ++ j)
					if(dcmp(fabs(d - dis[i][sub[i][j]]) - r[sub[i][j]]) <= 0 && !vis[n + sub[i][j]]){
						vis[n + sub[i][j]] = true;
						q.push(n + sub[i][j]); break;
					}
			}else if(!vis[i]) vis[i] = true, q.push(i);
		}
		while(!q.empty()){
			now = q.front(); q.pop();
			for(i = 0; i < n; ++ i)
				if(g[now][i] && !vis[i])
					vis[i] = true, q.push(i);
		}
		for(i = 0; i < n; ++ i){
			d = sqrt(1.0 * (x[i] - tx) * (x[i] - tx) + 1.0 * (y[i] - ty) * (y[i] - ty));
			if(dcmp(d - r[i]) > 0) continue;
			if(d > r[i]) continue;
			if(vis[n + i]){
				if(dcmp(d - r[i]) <= 0) return "YES";
			}else if(vis[i]){
				if(dcmp(d - r[i]) <= 0 && dcmp(d - mind[i]) >= 0) return "YES";
			}
			for(j = 0; j < int(sub[i].size()); ++ j)
				if(vis[n + sub[i][j]] && dcmp(fabs(d - dis[i][sub[i][j]]) - r[sub[i][j]]) <= 0)
					return "YES";
		} return "NO";
	}
};
