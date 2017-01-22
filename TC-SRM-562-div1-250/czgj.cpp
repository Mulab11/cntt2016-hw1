/*
	Some simple magic.
	Only consider the last n pastes.
	The first ones are equal to the last nth paste.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class PastingPaintingDivOne {
	public:
	vector<long long> countColors(vector <string> clipboard, int T) {
		LL R, G, B, e, r0, g0, b0; R = G = B = r0 = g0 = b0 = e = 0;
		char st[233][233]; memset(st, '.', sizeof st); // The map
		int layer[233][233]; // When each block is finally covered
		int n = clipboard.size(), m = clipboard[0].length();
		for (int i = 0; i < T && i < n; ++i) //Do the last n pastes
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < m; ++k)
					if (clipboard[j][k] != '.')
						st[i + j][i + k] = clipboard[j][k], layer[i + j][i + k] = i + 1;
		for (int i = 0; i < 100; ++i) // Do the counting
			for (int j = 0; j < 100; ++j)
				++(st[i][j] == 'R' ? R : st[i][j] == 'G' ? G : st[i][j] == 'B' ? B : e);
		if (T > n){
			for (int i = 0; i < n; ++i) // Count the first layer
				for (int j = 0; j < m; ++j)
					if (layer[i][j] == 1) ++(st[i][j] == 'R' ? r0 : st[i][j] == 'G' ? g0 : st[i][j] == 'B' ? b0 : e);
			R += r0 * (T - n); G += g0 * (T - n); B += b0 * (T - n);
		}
		vector<LL> ret; ret.push_back(R); ret.push_back(G); ret.push_back(B);
		return ret;
	}
};

/*
	Miracle painting
	Kiseki no showtime
		- Miracle Paint
*/

