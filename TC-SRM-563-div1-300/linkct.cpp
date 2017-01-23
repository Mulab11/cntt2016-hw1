#include <bits/stdc++.h>
using namespace std;

class FoxAndHandle{
public:
	string lexSmallestName(string s){
		int i, j, k, l, pos, cnt[27], cur[27], n;
		memset(cnt, 0, sizeof(cnt));
		string ans; n = s.length();
		for(i = 0; i < n; ++ i)
			++ cnt[s[i] - 'a'];
		for(i = 0; i < 26; ++ i) cnt[i] /= 2;
		for(i = 1, j = 0; i <= n / 2; ++ i){
			for(k = 0; k < 26; ++ k){
				if(!cnt[k]) continue;
				for(l = j; l < n; ++ l)
					if(s[l] == k + 'a') break;
				pos = l;
				memset(cur, 0, sizeof(cur));
				for(; l < n; ++ l)
					++ cur[s[l] - 'a'];
				for(l = 0; l < 26; ++ l)
					if(cur[l] < cnt[l])
						break;
				if(l == 26) break;
			} j = pos + 1, ans += ('a' + k), -- cnt[k];
		} return ans;
	}
};
