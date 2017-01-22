/*
	Network Flow
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int MAXN = 3000;
const int MAXM = 200000;
struct costflow{ // flow
	int hd[MAXN], pre[MAXN], to[MAXM], nxt[MAXM], flow[MAXM], w[MAXM], tl;
	void add0(int u, int v, int f0, int w0){
		++tl; nxt[tl] = hd[u]; to[tl] = v; flow[tl] = f0; w[tl] = w0; hd[u] = tl;
	}
	void add(int u, int v, int f0, int w0){
		add0(u, v, f0, w0); add0(v, u, 0, -w0);
	}
	void allclear(){
		memset(hd, 0, sizeof hd); tl = 1;
	}
	int dis[MAXN];
	bool SPFA(int s, int t) {
		static int q[MAXM];
		static bool inq[MAXN];
		memset(inq, 0, sizeof inq);
		memset(dis, 0x3f, sizeof dis);
		memset(pre, 0xff, sizeof pre);
		int l = 0, r = 1; q[0] = s; dis[s] = 0;
		while (l < r) {
			int u = q[l++], v; inq[u] = 0;
			for (int i = hd[u]; i; i = nxt[i])
				if (flow[i] && dis[v = to[i]] > dis[u] + w[i]) {
					pre[v] = i; dis[v] = dis[u] + w[i];
					if (!inq[v]) {inq[v] = 1; q[r++] = v;}
				}
		}
		return dis[t] != (int)0x3f3f3f3f;
	}
	PI Flow(int s, int t){
		int ret = 0, f = 0;
		while (SPFA(s, t)) {
			for (int i = pre[t]; ~i; i = pre[to[i ^ 1]]) --flow[i], ++flow[i ^ 1];
			ret += dis[t]; ++f;
		}
		return PI(f, ret);
	}
}G;
int n, m;
vector<string> a;
int getid(int x, int y){
	if (x < 0 || x >= n || y < 0 || y >= m || a[x][y] == 'w') return -1; // return -1 on invalid positions
	return (x * m + y) * 3;
}
class CurvyonRails {
	public:
	int getmin(vector <string> a) {
		G.allclear(); ::a = a;
		n = a.size(); m = a[0].size();
		int S = n * m * 3, T = S + 1, cnt = 0;
		rep(i, 0, n - 1) rep(j, 0, m - 1) if(a[i][j] != 'w'){
			++cnt;
			int id = getid(i, j), id1 = id + 1, id2 = id + 2;
			if ((i ^ j) & 1){ // S side
				G.add(S, id, 2, 0);
				if (a[i][j] == 'C'){ // extra cost for same-line rail
					G.add(id, id1, 1, 0);
					G.add(id, id1, 1, 1);
					G.add(id, id2, 1, 0);
					G.add(id, id2, 1, 1);
				}
				else{ // no extra cost
					G.add(id, id1, 2, 0);
					G.add(id, id2, 2, 0);
				}
				// link adjacent cities
				int tid = getid(i - 1, j);
				if (tid != -1) G.add(id1, tid + 1, 1, 0);
				tid = getid(i + 1, j);
				if (tid != -1) G.add(id1, tid + 1, 1, 0);
				tid = getid(i, j - 1);
				if (tid != -1) G.add(id2, tid + 2, 1, 0);
				tid = getid(i, j + 1);
				if (tid != -1) G.add(id2, tid + 2, 1, 0);
			}
			else{ // T side, similar to above
				G.add(id, T, 2, 0);
				if (a[i][j] == 'C'){
					G.add(id1, id, 1, 0);
					G.add(id1, id, 1, 1);
					G.add(id2, id, 1, 0);
					G.add(id2, id, 1, 1);
				}
				else{
					G.add(id1, id, 2, 0);
					G.add(id2, id, 2, 0);
				}
			}
		}
		PI r = G.Flow(S, T);
		return r.first != cnt ? -1 : r.second;
	}
};

/*
	Another flowwwwwwww
	flow is power
	flow is justice
*/
