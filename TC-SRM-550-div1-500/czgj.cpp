/*
	Some tricky math(?).
	Some transfer --> Sierpinski triangle
	F[i][j] = C(i, j) mod 2 = ![(~i) & j]
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
class CheckerExpansion {
	public:
	vector <string> resultAfter(LL t, LL x0, LL y0, int w, int h) {
		vector<string> ret(h, string(w, '.'));
		for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j){
			LL x = x0 + j, y = y0 + h - i - 1;
			if ((x + y) % 2 || x < y) continue;
			LL u = (x + y) / 2, v = (x - y) / 2;
			if (u >= t || (~u) & v) continue;
			ret[i][j] = u & 1 ? 'B' : 'A';
		}
		return ret;
	}
};

/*
	'TATOE sekai no subete ga miiro ni toketemo kitto
	anata no koe ga suru
	daijoubu kaeroutte demo'
		- Miiro
*/
