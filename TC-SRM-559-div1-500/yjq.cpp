#include <bits/stdc++.h>

using namespace std;

int n ;

typedef long long LL ; 

const int MAXN = 60 ; 

int siz[MAXN], md ;

bool mp[MAXN][MAXN] ; 


void Dfs2(int cur, int fr) {
		siz[cur] = 1;
		for(int v = 0; v < n; v++) {
				if(mp[cur][v] && v != fr)
						Dfs2(v, cur), siz[cur] += siz[v];
		}
}

vector<int> son ; 
LL Dfs(int cur, int fr, int id) {
		md = max(md, id); 
		son.clear() ; 
		for(int v = 0; v < n; v++) {
				if(mp[cur][v] && v != fr)
						son.push_back(v);
		}
		if(son.size() > 2) return 0;
		if(son.size() == 0) return 1;
		if(son.size() == 2 && siz[son[0]] < siz[son[1]])
				swap(son[0], son[1]);
		LL ret = 1;
		for(int i = 0; i < son.size(); i++) ret *= Dfs(son[i], cur, id * 2 + i);
		if(son.size() > 1 && siz[son[0]] == siz[son[1]]) ret *= 2;
		return ret;
}
class HatRack {
		public:
				LL countWays(vector<int> eu, vector<int> ev) {
						n = eu.size() + 1;
						if(n == 2) return 2;
						for(int i = 0; i + 1 < n; i++) {
								--eu[i], --ev[i] ; 
								mp[eu[i]][ev[i]] = mp[ev[i]][eu[i]] = 1;
						}
						LL ans = 0;
						for(int i = 0; i < n; i++) {
								Dfs2(i, -1);
								md = 0;
								LL tmp = Dfs(i, -1, 1);
								if(md == n) ans += tmp;
						}
						return ans;
				}
} sol ;

		
