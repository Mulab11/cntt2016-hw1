/*
	I don't think this is right...
	But it passed all test cases.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
int cnt[60][26];
bool used[26];
int n;
class StringGame {
	public:
	vector <int> getWinningStrings(vector <string> S) {
		vector<int> ret, rest, tmp; n = S.size(); memset(cnt, 0, sizeof cnt);
		rep(i, 0, n - 1) rep(j, 0, (int)S[i].length() - 1) ++cnt[i][S[i][j] - 'a'];
		rep(i, 0, n - 1){
			memset(used, 0, sizeof used); rest.clear();
			rep(j, 0, n - 1) if (i != j) rest.push_back(j);
			rep(T, 1, 26){
				rep(c, 0, 25){
					if (used[c]) continue;
					bool ok = 1;
					rep(j, 0, (int)rest.size() - 1) if (cnt[rest[j]][c] > cnt[i][c]) {ok = 0; break;}
					if (!ok) continue;
					tmp.clear(); rep(j, 0, (int)rest.size() - 1) if (cnt[rest[j]][c] == cnt[i][c]) tmp.push_back(rest[j]);
					used[c] = 1; rest = tmp; break;
				}
				if (rest.empty()){ret.push_back(i); break;}
			}
		}
		return ret;
	}
};

/*
	Atama ga \PARN/
*/
