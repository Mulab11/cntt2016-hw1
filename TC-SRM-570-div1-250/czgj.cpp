/*
	Implementation.
	Herb must runs a cycle of 4 rounds.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
class RobotHerb {
	public:
	long long getdist(int T, vector <int> a) {
		LL x[5] = {0}, y[5] = {0}, tx = 0, ty = 0, d = 0;
		int n = a.size();
		for (int i = 1; i <= 4; ++i){ // Run the first 4 rounds.
			for (int j = 0; j < n; ++j)
				tx += dx[d] * a[j], ty += dy[d] * a[j], d = (d + a[j]) % 4;
			x[i] = tx; y[i] = ty;
		}
		tx = x[4] * (T / 4) + x[T % 4]; // Calculate the final coordinates
		ty = y[4] * (T / 4) + y[T % 4];
		return abs(tx) + abs(ty);
	}
};

/*
	san ten ichi yon ichi go (9) ni roku go san go hachi (9) nana (9) san ni san hachi yon roku ni roku...
		- Hatsune Miku ga Enshuuritsu 10,000keta Oboeta you desu  
*/

