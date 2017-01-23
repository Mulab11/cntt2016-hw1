#include <bits/stdc++.h>
using namespace std;

class XorTravelingSalesman{
public:
	int n, d[15], vis[55]; queue <int> q;
	void add(int x){
		for(int i = 9; i >= 0; -- i){
			if((x & (1 << i)) == 0) continue;
			if(d[i]) x ^= d[i];
			else{d[i] = x; break;}
		}
	}
	int calc(){
		int ret = 0, i;
		for(i = 9; i >= 0; -- i)
			ret = max(ret, ret ^ d[i]);
		return ret;
	}
	int maxProfit(vector <int> val, vector <string> g){
		int i, now;
		n = g.size();
		q.push(0); vis[0] = true;
		while(!q.empty()){
			now = q.front(); q.pop();
			add(val[now]);
			for(i = 0; i < n; ++ i)
				if(g[now][i] == 'Y' && !vis[i])
					vis[i] = true, q.push(i);
		} return calc();
	}
};
