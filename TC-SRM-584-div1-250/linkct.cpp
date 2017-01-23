#include <bits/stdc++.h>
using namespace std;

class Egalitarianism{
public:
	int n, g[55][55];
	int maxDifference(vector <string> g_, int D){
		int i, j, k, mx = 0;
		n = g_.size();
		for(i = 0; i < n; ++ i){
			for(j = 0; j < n; ++ j)
				g[i][j] = (g_[i][j] == 'Y' ? 1 : n);
			g[i][i] = 0;
		}
		for(k = 0; k < n; ++ k)
			for(i = 0; i < n; ++ i)
				for(j = 0; j < n; ++ j)
					if(g[i][j] > g[i][k] + g[k][j])
						g[i][j] = g[i][k] + g[k][j];
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j)
				if(g[i][j] > mx)
					mx = g[i][j];
		return mx >= n ? -1 : (mx * D);
	}
};
