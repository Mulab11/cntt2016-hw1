#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;

class History {
private :
	int n, m;
	int cht[27][12], num[27];
	int dis[27][27];

	inline void trans(int &x, int &y, int &a, int &b, const string &s) {
		assert(s[2] == '-');
		x = s[0] - 'A';
		y = s[1] - '0';
		a = s[3] - 'A';
		b = s[4] - '0';
	}
public :
	//差分约数，最短路
	string verifyClaims(vector<string> dat, vector<string> bat, vector<string> que) {
		stringstream ss;
		n = dat.size();
		memset(dis, -0x3f, sizeof(dis));
		rep (i, 0, n-1) dis[i][i] = 0;
		rep (i, 0, n-1) {
			ss << dat[i];
			while (ss >> cht[i][num[i]++]);
			ss.clear();
		}
		rep (i, 0, bat.size()-1) ss << bat[i];
		string bs;
		int x, y, a, b;
		while (ss >> bs) {
			trans(x, y, a, b, bs);
			int l = cht[x][y + 1] - cht[a][b] - 1;
			int r = cht[a][b + 1] - cht[x][y] - 1;
			upmax(dis[a][x], -l);
			upmax(dis[x][a], -r);
		}
		rep (k, 0, n-1) rep (i, 0, n-1) rep (j, 0, n-1) {
			upmax(dis[i][j], dis[i][k] + dis[k][j]);
		}
		m = que.size();
		string res(m, 'N');
		rep (i, 0, m-1) {
			trans(x, y, a, b, que[i]);
			if (cht[x][y + 1] - cht[a][b] - 1 < dis[x][a]) {
				continue ;
			}
			if (cht[a][b + 1] - cht[x][y] - 1 < dis[a][x]) {
				continue ;
			}
			res[i] = 'Y';
		}
		return res;
	}
};
