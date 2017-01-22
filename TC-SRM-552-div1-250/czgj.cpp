/*
	Eazy Math.
	No comment.
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
class FoxPaintingBalls {
	public:
	long long theMax(long long R, long long G, long long B, int N) {
		LL S = (LL)N * (N + 1) / 2, t = S / 3;
		return min(t ? min(min(R, G), B) / t : (LL)(~0ull>>1), (R + G + B) / S);
	}
};

/*
	'Yukkuri shite itte ne!!
	baka baka baka baka baka baka'
		- Cirno's Perfect Math Class
*/
