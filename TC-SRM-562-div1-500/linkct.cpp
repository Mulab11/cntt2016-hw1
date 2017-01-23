#include <bits/stdc++.h>
using namespace std;
const int MAXN = 225;
typedef long long int LL;
typedef vector <string> vs;

class CheckerFreeness{
public:
	struct Point{
		int x, y;
		Point(){}
		Point(int a, int b) :x(a), y(b) {}
		Point operator - (const Point &rhs) const{
			return Point(x - rhs.x, y - rhs.y);
		}
	}w[MAXN], b[MAXN];
	LL Cross(Point a, Point c){return LL(a.x) * c.y - LL(a.y) * c.x;}
	int n, m, wx[MAXN], wy[MAXN], bx[MAXN], by[MAXN];
	bitset <MAXN> lft[MAXN][MAXN], rht[MAXN][MAXN], L, R;
	void extract(vs &inp, int seq[], int &len){
		for(len = 1; len < int(inp.size()); ++ len)
			inp[0] += inp[len];
		stringstream readin(inp[0]);
		for(len = 0; readin >> seq[++ len]; ) ;
	}
	string isFree(vs wx_, vs wy_, vs bx_, vs by_){
		int i, j, k;
		extract(wx_, wx, n);
		extract(wy_, wy, n);
		extract(bx_, bx, m);
		extract(by_, by, m);
		-- n, -- m;
		for(i = 1; i <= n; ++ i)
			w[i] = Point(wx[i], wy[i]);
		for(i = 1; i <= m; ++ i)
			b[i] = Point(bx[i], by[i]);
		for(i = 1; i <= m; ++ i)
			for(j = 1; j <= n; ++ j)
				for(k = 1; k <= m; ++ k)
					if(Cross(w[j] - b[i], b[k] - b[i]) > 0)
						lft[i][j][k] = true; //Black point k is to the left of the vector (black point i -> white point j)
					else rht[i][j][k] = true;
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= n; ++ j){
				L.reset(), R.reset();
				for(k = 1; k <= m; ++ k)
					if(Cross(w[j] - w[i], b[k] - w[i]) > 0) L[k] = true;
					else R[k] = true;
				for(k = 1; k <= m; ++ k)
					if(L[k]){
						if(Cross(w[i] - b[k], w[j] - b[k]) > 0){
							if((lft[k][i] & rht[k][j] & R).any()) return "YES"; //Answer must lay in the opposite side of (w.p. i -> w.p. j) of k
						}else if((lft[k][j] & rht[k][i] & R).any()) return "YES";
					}else{
						if(Cross(w[i] - b[k], w[j] - b[k]) > 0){
							if((lft[k][i] & rht[k][j] & L).any()) return "YES";
						}else if((lft[k][j] & rht[k][i] & L).any()) return "YES";
					}
			}
		return "NO";
	}
};
