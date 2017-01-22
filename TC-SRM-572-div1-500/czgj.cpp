/*
	Meet-in-the-Middle
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef map<string, vector<string> > MSVS;
typedef MSVS::iterator MSVSIT;
const int MAXN = 60;
int n, m;
int bull[MAXN], cnt[MAXN];
vector<int> pos[MAXN][MAXN];
MSVS S[2];
string trans(string a){ // a -> goal - a
	string ret;
	rep(i, 0, (int)a.length() - 1) ret += bull[i] - (a[i] - '0') + '0';
	return ret;
}
void dfs(string s, int now, int end, int pp){
	if (now == end){ // end
		string t;
		rep(i, 0, m - 1) t += '0' + cnt[i]; 
		S[pp][t].push_back(s); 
		return;
	}
	rep(i, 0, 9){
		rep(j, 0, (int)pos[now][i].size() - 1) ++cnt[pos[now][i][j]]; // upd
		dfs(s + (char)('0' + i), now + 1, end, pp);
		rep(j, 0, (int)pos[now][i].size() - 1) --cnt[pos[now][i][j]]; // undo
	}
}
class EllysBulls {
	public:
	string getNumber(vector <string> guesses, vector <int> bulls) {
		n = guesses[0].length(); m = bulls.size();
		S[0].clear(); S[1].clear();
		rep(i, 0, n - 1) rep(j, 0, 9) pos[i][j].clear();
		rep(i, 0, m - 1) bull[i] = bulls[i];
		rep(i, 0, m - 1) rep(j, 0, n - 1) pos[j][guesses[i][j] - '0'].push_back(i);
		dfs("", 0, n / 2, 0); dfs("", n / 2, n, 1);
		string ret;
		for (MSVSIT it = S[0].begin(); it != S[0].end(); ++it){
			MSVSIT it2 = S[1].find(trans(it->first)); // find the other
			if (it2 == S[1].end()) continue; // not found
			if (it->second.size() > 1 || it2->second.size() > 1 || ret != "") return "Ambiguity"; // too many
			ret = it->second[0] + it2->second[0]; // upd
		}
		return ret == "" ? "Liar" : ret;
	}
};

/*
	dreamoon --> doraemon
	(?)
*/

