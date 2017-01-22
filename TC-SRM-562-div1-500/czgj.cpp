/*
	Brute force with bitset.
*/
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
struct point{
	LL x, y;
};
LL cross(const point& a, const point& b){
	return a.x * b.y - a.y * b.x;
}
point operator -(const point& a, const point& b){
	return point{a.x - b.x, a.y - b.y};
}
const int MAXN = 233;
point A[MAXN], B[MAXN];
bitset<MAXN> F[MAXN][MAXN][2], G[MAXN][MAXN];
class CheckerFreeness {
	public:
	void getargs(vector<string> st, vector<int>& ret){
		int t = 0; ret.clear();
		for (int i = 0; i < st.size(); ++i)
			for (int j = 0; j < st[i].length(); ++j)
				if (st[i][j] == ' ') ret.push_back(t), t = 0;
					else t = t * 10 + st[i][j] - '0';
		ret.push_back(t);
	}
	string isFree(vector <string> _whiteX, vector <string> _whiteY, vector <string> _blackX, vector <string> _blackY) {
		vector<int> wX, wY, bX, bY;
		getargs(_whiteX, wX); getargs(_whiteY, wY); getargs(_blackX, bX); getargs(_blackY, bY);
		int n = wX.size(), m = bX.size();
		rep(i, 0, n - 1) A[i] = point{wX[i], wY[i]};
		rep(i, 0, m - 1) B[i] = point{bX[i], bY[i]};
		rep(i, 0, m - 1) rep(j, 0, n - 1){
			F[i][j][0].reset(); F[i][j][1].reset();
			rep(k, 0, m - 1){
				LL t = cross(A[j] - B[i], B[k] - B[i]);
				if (t < 0) F[i][j][0].set(k); // k is to the right of i->j
				if (t > 0) F[i][j][1].set(k); // left
			}
		}
		rep(i, 0, n - 1) rep(j, 0, i - 1){
			G[i][j].reset();
			rep(k, 0, m - 1)
				if (cross(A[j] - A[i], B[k] - A[i]) > 0) // k is to the left of i->j
					G[i][j].set(k);
		}
		rep(i, 0, n - 1) rep(j, 0, i - 1) rep(k, 0, m - 1)
			if (!G[i][j][k] && (F[k][i][0] & F[k][j][1] & G[i][j]).count())
				return "NO";
		return "YES";
	}
};

/*
	Ni-
	conico douga
*/
