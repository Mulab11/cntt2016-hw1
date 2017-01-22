/*
	System of difference constraints
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 33;
vector<int> t[MAXN];
int g[MAXN][MAXN];
class History {
	public:
	bool read(stringstream& ss, int &X, int &a, int &Y, int &b){ // Read a formatted battle
		string t; if (!(ss >> t)) return 0;
		X = t[0] - 'A'; a = t[1] - '0'; Y = t[3] - 'A'; b = t[4] - '0';
		return 1;
	}
	void readbattles(const vector<string> &battles){ // Read battles & make the graph
		string s; rep(i, 0, (int)battles.size() - 1) s += battles[i];
		stringstream ss(s); int X, a, Y, b;
		while (read(ss, X, a, Y, b)){
			g[X][Y] = min(g[X][Y], t[X][a + 1] - t[Y][b] - 1);
			g[Y][X] = min(g[Y][X], t[Y][b + 1] - t[X][a] -   1);
		}
	}
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {
		int n = dynasties.size();
		rep(i, 0, n - 1) t[i].clear();
		rep(i, 0, n - 1) rep(j, 0, n - 1) if (i != j) g[i][j] = 1e9;
		rep(i, 0, n - 1){
			stringstream ss(dynasties[i]); int a;
			while (ss >> a) t[i].push_back(a);
		}
		readbattles(battles);
		rep(k, 0, n - 1) rep(i, 0, n - 1) rep(j, 0, n - 1) // Floyd
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		string ret;
		rep(i, 0, (int)queries.size() - 1){
			int X, a, Y, b; stringstream ss(queries[i]);
			if (!read(ss, X, a, Y, b)) continue;
			ret += (-g[X][Y] <= t[Y][b + 1] - t[X][a] - 1) && (g[Y][X] >= t[Y][b] - t[X][a + 1] + 1) ? 'Y' : 'N'; // Judge
		}
		return ret;
	}
};

/*
	Sore ga owari ka...
	Yoroshii desu
*/
