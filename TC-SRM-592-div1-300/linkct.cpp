#include <bits/stdc++.h>
using namespace std;

class LittleElephantAndBalls{
public:
	int getNumber(string s){
		int i, ans = 0, cnt[26];
		memset(cnt, 0, sizeof(cnt));
		for(i = 0; i < int(s.length()); ++ i){
			ans += min(cnt['R' - 'A'], 2) + min(cnt['G' - 'A'], 2) + min(cnt['B' - 'A'], 2);
			++ cnt[s[i] - 'A'];
		} return ans;
	}
};
