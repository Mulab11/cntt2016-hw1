#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
const int MAXN = 55;

class CirclesGame{
public:
	vector <int> son[MAXN]; bool nxt[MAXN];
	int n, sg[MAXN], fa[MAXN];
	inline int sqr(int x){return x * x;}
	void trans(int x, int sum){
		int i;
		for(i = 0; i < int(son[x].size()); ++ i)
			sum ^= sg[son[x][i]];
		nxt[sum] = true;
		for(i = 0; i < int(son[x].size()); ++ i)
			trans(son[x][i], sum ^ sg[son[x][i]]);
	}
	int dfs(int x){
		int i;
		for(i = 0; i < int(son[x].size()); ++ i)
			dfs(son[x][i]);
		memset(nxt, false, sizeof(nxt));
		trans(x, 0);
		for(i = 0; nxt[i]; ++ i) ;
		return sg[x] = i;
	}
	string whoCanWin(vi x, vi y, vi r){
		int i, j, ans = 0, mn; n = x.size();
		memset(fa, -1, sizeof(fa));
		for(i = 0; i < n; ++ i){
			for(j = 0, mn = -1; j < n; ++ j)
				if(sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j])) + r[i] < r[j])
					if(fa[i] == -1 || r[j] < mn) mn = r[j], fa[i] = j;
			if(fa[i] == -1) fa[i] = i;
			if(fa[i] != i) son[fa[i]].push_back(i);
		}
		for(i = 0; i < n; ++ i)
			if(fa[i] == i) ans ^= dfs(i);
		return ans ? "Alice" : "Bob";
	}
};
