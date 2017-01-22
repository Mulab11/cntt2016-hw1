/*
	Shortest path.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;

class Egalitarianism {
	public:
	int maxDifference(vector <string> isFriend, int d) {
		int G[99][99], n = isFriend.size(), mx = 0;
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
			G[i][j] = i == j ? 0 : isFriend[i][j] == 'Y' ? 1 : 99;
		for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
			if (G[i][j] > G[i][k] + G[k][j]) G[i][j] = G[i][k] + G[k][j];
		for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
			mx = max(mx, G[i][j]);
		return mx < 99 ? mx * d : -1;
	}
};

/*
	Aa mou itai itai nante
	Koe wa tashikani todoite tan desu
	Kimi ga kirai kirai nante
	Kotoba sabi tsuite kikoenai ya
		- Toumei Elegy
*/
