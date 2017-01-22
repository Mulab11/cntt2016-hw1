/*
	Shortest path.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;

int G[80][80];
int n;
class ColorfulWolves {
	public:
	int getmin(vector <string> colormap) {
		n = colormap.size();
		for (int i = 0; i < n; ++i){
			int cnt = 0;
			for (int j = 0; j < n; ++j)
				G[i][j] = colormap[i][j] == 'N' ? 2333333 : cnt++;
		}
		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
		return G[0][n - 1] >= 2333333 ? -1 : G[0][n - 1];
	}
};

/*
	'Click the circles'
		- circles!
*/
