#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;

class NextAndPrev{
public:
	vector <pii> match; vector <int> pos[26];
	int n, m, gol, gor;
	inline int calc(int l, int r, int p){
		if(p < l) return (r - p) * gol;
		if(p > r) return (p - l) * gor;
		return (p - l) * gor + (r - p) * gol;
	}
	int getMinimum(int inc, int dec, string st, string ed){
		if(st == ed) return 0;
		gor = inc, gol = dec, n = st.length();
		int i, j, k, cur, ans = 1e9, dt;
		for(i = 0; i < n; ++ i)
			pos[st[i] - 'a'].push_back(i);
		for(i = 0; i < 26; ++ i){
			if(pos[i].empty()) continue;
			for(j = 1; j < int(pos[i].size()); ++ j)
				if(ed[pos[i][j]] != ed[pos[i][j - 1]])
					return -1;
			match.push_back(pii(i, ed[pos[i][0]] - 'a'));
		} m = match.size();
		if(m == 26){
			bool occur[26];
			memset(occur, false, sizeof(occur));
			for(i = 0; i < m; ++ i)
				occur[match[i].se] = true;
			for(i = 0; i < 26; ++ i)
				if(!occur[i]) break;
			if(i == 26) return -1;
		}
		for(i = 0; i < m; ++ i){
			for(j = i + 1; j < i + m; ++ j)
				if(match[j - 1].se > match[j].se)
					break;
			if(j == i + m){
				for(dt = - 26; dt <= 52; dt += 26){
					for(j = k = i, cur = 0; j < i + m; ++ j){
						if(j == i || match[j].se == match[j - 1].se)
							continue;
						cur += calc(match[k].fi, match[j - 1].fi, match[k].se + dt);
						//process [k, j - 1]
						k = j;
					} ans = min(ans, cur + calc(match[k].fi, match[j - 1].fi, match[k].se + dt));
				}
			} match.push_back(pii(match[i].fi + 26, match[i].se));
		} return ans < int(1e9) ? ans : -1;
	}
};
