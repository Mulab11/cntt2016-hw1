#include <bits/stdc++.h>
using namespace std;

class TurnOnLamps{
public:
	int f[55], g[55], n;
	int minimize(vector <int> fa, string init, string imp){
		int i, f_, g_;
		n = fa.size() + 1;
		for(i = 0; i < n; ++ i) f[i] = 0, g[i] = 1;
		for(i = n - 1; i; -- i){
			if(imp[i - 1] == '1'){
				if(init[i - 1] == '1') g[i] = 1e9;
				else f[i] = 1e9;
			}
			f_ = min(f[fa[i - 1]] + f[i], g[fa[i - 1]] + g[i]);
			g_ = min(f[fa[i - 1]] + g[i], g[fa[i - 1]] + f[i]);
			f[fa[i - 1]] = f_, g[fa[i - 1]] = g_;
		} return f[0];
	}
};
