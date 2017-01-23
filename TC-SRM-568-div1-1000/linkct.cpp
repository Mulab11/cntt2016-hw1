#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class DisjointSemicircles{
public:
	struct semiCircle{
		int l, r, l_, r_;
		bool operator < (const semiCircle &rhs) const{
			return l_ < rhs.l_;
		}
	}circ[MAXN];
	int mp[MAXN], f[MAXN], val[MAXN], l[MAXN], r[MAXN];
	int s0[MAXN], s1[MAXN], t0, t1;
	int find(int x){
		if(f[x] == -1) return x;
		int fa = find(f[x]);
		val[x] ^= val[f[x]];
		return f[x] = fa;
	}
	bool merge(int u, int v, int w){
		int u_ = find(u), v_ = find(v), dt = w ^ val[u] ^ val[v];
		if(u_ == v_) return val[u_] != dt;
		f[u_] = v_, val[u_] = dt;
		return false;
	}
	bool push(int stk[], int &top, int v){ //Check for range intersection with a stack; every range contains all ranges to the top of it
		while(circ[v].l_ > circ[stk[top]].r_) -- top;
		if(circ[v].r_ > circ[stk[top]].r_) return true;
		stk[++ top] = v; return false;
	}
	string getPossibility(vector <int> label){
		int i, j, N = label.size(), n = 0, m = 0;
		memset(mp, -1, sizeof(mp));
		for(i = 0; i < N; ++ i)
			if(~label[i]){
				if(mp[label[i]] == -1){
					circ[mp[label[i]] = m ++].l = n;
					circ[mp[label[i]]].l_ = i;
				}else{
					circ[mp[label[i]]].r = n;
					circ[mp[label[i]]].r_ = i;
				}
			}else ++ n;
		sort(circ, circ + m);
		circ[m].l_ = -1, circ[m].r_ = N;
		for(i = 0; i < (1 << m); ++ i){ //Enumerate directions for semicircles that already existed
			memset(f, -1, sizeof(f));
			memset(val, 0, sizeof(val));
			s0[t0 = 1] = s1[t1 = 1] = m;
			merge(0, n, 0);
			for(j = 0; j < m; ++ j) //Check for intersections & validity of the other points
				if(i & (1 << j)){
					if(push(s1, t1, j) || merge(circ[j].l, circ[j].r, 0)) break;
				}else if(push(s0, t0, j) || merge(circ[j].l, circ[j].r, (circ[j].l ^ circ[j].r) & 1)) break;
			if(j == m) return "POSSIBLE";
		} return "IMPOSSIBLE";
	}
};
