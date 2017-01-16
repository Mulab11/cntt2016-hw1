#line 2 "FoxTheLinguist.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int V = 101, E = V + 200 + 10, INF = 1e9;

int vn, en;
struct edge {
	int u, v, w;
	edge(int _u = 0, int _v = 0, int _w = 0):u(_u), v(_v), w(_w) {}
}e[E + 9];

int rt;

int in[V + 9];
int fa[V + 9];
int vis[V + 9];
int id[V + 9];

int direct_mst() {// 最小树形图，朱刘算法
	int ret = 0;
	while(true) {
		std::fill(in, in + vn, INF);
		std::fill(fa, fa + vn, -1);
		for(int i = 0; i < en; ++i) {// in[v] 表示到v的边中最小的权值
			int u = e[i].u, v = e[i].v, w = e[i].w;
			if(u != v && in[v] > w) in[v] = w, fa[v] = u;
		}
		for(int i = 0; i < vn; ++i)
			if(i != rt && fa[i] == -1)// 有除根外的点无法找到父亲，无解
				return -1;
		std::fill(vis, vis + vn, -1);
		int tot = 0;
		id[rt] = tot++;
		// id[i] 表示原图中点i在新图中的编号
		for(int i = 0; i < vn; ++i) {
			if(i != rt) ret += in[i];
			if(vis[i] == -1) {// 找环
				int x = i;
				while(vis[x] == -1 && x != rt)
					vis[x] = i, x = fa[x];
				if(x == rt || vis[x] != i) {// 无环
					int x = i;
					while(vis[x] == i && x != rt)
						id[x] = tot++, x = fa[x];
				}
				else {// 有环，注意考虑ρ型环
					int y = i;
					while(y != x)
						id[y] = tot++, y = fa[y];
					y = x, id[y] = tot++, y = fa[y];
					while(y != x)
						id[y] = tot - 1, y = fa[y];
				}
			}
		}
		if(tot == vn) break;// 无环了，结束
		// 更新边权，点的编号
		for(int i = 0; i < en; ++i) {
			int u = id[e[i].u], v = id[e[i].v];
			if(u != v) e[i].w -= in[e[i].v];
			e[i].u = u, e[i].v = v;
		}
		vn = tot, rt = id[rt];
	}
	return ret;
}

class FoxTheLinguist {  
public:  
	int minimalHours(int n, vector <string> courseInfo) {  
		std::string s;
		for(auto i : courseInfo) s += i;
		vn = 1 + n * 10, rt = n * 10, en = 0;
		for(int i = 0; i < SZ(s); ++i) {
			int u = (s[i] - 'A') * 10 + (s[i + 1] - '0');
			int v = (s[i + 4] - 'A') * 10 + (s[i + 5] - '0');
			int w = (s[i + 7] - '0') * 1000 + (s[i + 8] - '0') * 100 + (s[i + 9] - '0') * 10 + (s[i + 10] - '0');
			e[en++] = edge(u, v, w);
			i += 11;
		}
		// (A + i)(x) -> (A + i)(x - 1) 连边权为0的边
		for(int i = 0; i < n; ++i)
			for(int j = 1; j <= 9; ++j)
				e[en++] = edge(i * 10 + j, i * 10 + j - 1, 0);
		// 构造一个原点连向所有(A + i)(0)
		for(int i = 0; i < n; ++i)
			e[en++] = edge(rt, i * 10, 0);
		return direct_mst();
	}    
};  
