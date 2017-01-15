#line 2 "XorTravelingSalesman.cpp"  
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

#define in(x) ((x) << 1)
#define ou(x) ((x) << 1 | 1)

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 100;

int n;
std::vector<pii> adj[N + 9];

int pxv[N + 9];
std::vector<int> cxv;
std::queue<int> q;

int base[12];

class XorTravelingSalesman {  
public:  
	int maxProfit(vector <int> val, vector <string> roads) {
		// n means the number of nodes
		n = SZ(val);
		for(int i = 0; i < 2 * n; ++i) adj[i].clear();
		// split a node x into 2 nodes in(x), ou(x)
		// and add an edge with val[x] between them
		for(int i = 0; i < n; ++i) adj[in(i)].pb(mp(ou(i), val[i]));
		// build a new graph with 2n nodes
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(roads[i][j] == 'Y')
					adj[ou(i)].pb(mp(in(j), 0));
		// initialization
		memset(pxv, -1, sizeof pxv);
		cxv.clear();
		q.push(in(0)), pxv[in(0)] = 0;// pxv[i] means a path's xor value on bfs tree through 0 to i
		while(!q.empty()) {
			int x = q.front();
			q.pop();
			for(int i = 0; i < SZ(adj[x]); ++i) {
				int y = adj[x][i].fi, v = adj[x][i].se;
				if(pxv[y] == -1) {
					pxv[y] = pxv[x] ^ v;
					q.push(y);
				}
				else cxv.pb(pxv[x] ^ pxv[y] ^ v);// an edge back to ancestor means a circle
			}
		}
		// get linear base
		memset(base, 0, sizeof base);
		for(int i = 0; i < SZ(cxv); ++i)
			for(int j = 9; j >= 0; --j)
				if(cxv[i] >> j & 1) {
					if(!base[j]) {
						base[j] = cxv[i];
						break;
					}
					else cxv[i] ^= base[j];
				}
		// enumerate end point
		int ret = 0;
		for(int i = 0; i < 2 * n; ++i)
			if(pxv[i] != -1) {
				for(int j = 9; j >= 0; --j)
					if(!(pxv[i] >> j & 1))// if jth bit of pxv[i] is 0, we can xor base[j] to it to make it bigger
						pxv[i] ^= base[j];
				chkmax(ret, pxv[i]);// update answer
			}
		return ret;
	}    
};  
