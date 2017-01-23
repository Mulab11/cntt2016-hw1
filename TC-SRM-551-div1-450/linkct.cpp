#include <cstdio>
#include <vector>
#include <string>
using namespace std;
const int INF = 0x3f3f3f3f, MAXN = 55;

class ColorfulWolves{
	public:
		int n, g[MAXN][MAXN];
		int getmin(vector <string> str){
			int i, j, k; n = str.size();
			for(i = 1; i <= n; ++ i)
				for(j = 1, k = 0; j <= n; ++ j) //Construct the graph from the transition matrix
					if(str[i - 1][j - 1] == 'Y') g[i][j] = k ++;
					else g[i][j] = INF;
			for(k = 1; k <= n; ++ k) //Floyd
				for(i = 1; i <= n; ++ i)
					for(j = 1; j <= n; ++ j)
						if(g[i][j] > g[i][k] + g[k][j])
							g[i][j] = g[i][k] + g[k][j];
			return g[1][n] == INF ? -1 : g[1][n];
		}
};
