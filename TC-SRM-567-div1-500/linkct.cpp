#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, SIGMA = 27;

class StringGame{
public:
	int cnt[MAXN][SIGMA], n, m; bool done[MAXN], used[SIGMA];
	vector <int> getWinningStrings(vector <string> s){
		int i, j, k, l; vector <int> ans;
		n = s.size(), m = s[0].length();
		memset(cnt, 0, sizeof(cnt));
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j)
				++ cnt[i + 1][s[i][j] - 'a'];
		for(i = 1; i <= n; ++ i){ //Enumerate string s[i] as the answer
			memset(used, false, sizeof(used));
			memset(done, false, sizeof(done));
			done[i] = true;
			for(j = 1; j <= 26; ++ j){
				for(k = 0; k < 26; ++ k){ //Find a "secure" character
					if(used[k]) continue;
					for(l = 1; l <= n; ++ l)
						if(!done[l] && cnt[l][k] > cnt[i][k])
							break;
					if(l > n) break;
				} if(k == 26) break;
				used[k] = true;
				for(l = 1; l <= n; ++ l) //Eliminate potential adversary
					if(cnt[i][k] > cnt[l][k])
						done[l] = true;
			} if(j <= 26) continue;
			for(j = 1; j <= n; ++ j)
				if(!done[j]) break;
			if(j > n) ans.push_back(i - 1);
		} return ans;
	}
};
