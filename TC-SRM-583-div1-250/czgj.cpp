/*
	Shortest Path (with edge weight = 1).
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;

class TravelOnMars {
	public:
	int minTimes(vector <int> range, int startCity, int endCity) {
		int G[99][99], n = range.size();
		for (int i = 0; i <	n; ++i) for (int j = 0; j < n; ++j)
			G[i][j] = i == j ? 0 : min((n + i - j) % n, (n + j - i) % n) <= range[i] ? 1 : 99;
		for (int k = 0; k < n; ++k) for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
			if (G[i][j] > G[i][k] + G[k][j]) G[i][j] = G[i][k] + G[k][j];
		return G[startCity][endCity];
	}
};

/*
	I hear the sound of your voice
	I hear it echo inside my dreams
	Turning into memories as they start to fall away
		- Omoide Kakera
*/
